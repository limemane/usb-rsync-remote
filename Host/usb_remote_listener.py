import serial 
import serial.tools.list_ports
import time 
import subprocess
import logging
import re
import yaml 

##############################################
# Constants
##############################################

# Instructions
HANDSHAKE = "-HANDSHAKE="
HANDSHAKE_EXPECTED = "-HANDSHAKE=imaremote"
DO_ACTION = "-DOACTION="
SHOW_DATA = "-SHOWDATA="
END_OF_TASK = "-ENDOFTASK="

# Serial parameters
BAUD_RATE = 115200

# Config file path
CONFIG_FILE_PATH = "./config.yaml"

##############################################
# Functions
##############################################

# Function to load config file
def configFileLoader():
    with open(CONFIG_FILE_PATH, 'r') as file_descriptor:
        configData = yaml.safe_load(file_descriptor)
    return configData

# Function sending a message to the serial connected device
def sendMessage(serial_device, message_type, message_content): 
    serial_device.write(
        bytes(
            message_type + message_content, 
            'utf-8'
        )
    ) 
    time.sleep(0.05) 

# Function returning the device on the host machine given its pid and vid
def findDeviceByPidVid(esp32_pid, esp32_vid):
    serial_device = None
    # Scanning serial ports waiting for the right pid and vid
    for port in serial.tools.list_ports.comports():
        if port.vid == esp32_vid and port.pid == esp32_pid:
            # Found a device, initialize serial interface
            serial_device = serial.Serial(
                port=port.device, 
                baudrate=BAUD_RATE, 
                timeout=None
            ) 
            # Do handshake
            logging.warning("Sending handshake")
            sendMessage(serial_device, HANDSHAKE, "iamhost") 
            logging.warning("Awaiting handshake response")
            if serial_device.isOpen():
                # Waiting 1 second for handshake response
                serial_device.timeout = 5
                input_data = serial_device.readline().strip().decode("utf-8")
                logging.warning("Received serial message : " + input_data)
                if HANDSHAKE_EXPECTED in input_data: 
                    # Device found, reset timeout to None
                    serial_device.timeout = None
                    # Store device port and break loop
                    logging.warning(f"Handshake OK, device port is: {port}")
                    break
                else:
                    serial_device.close()
                    serial_device = None
            else:
                serial_device.close()
                serial_device = None

    return serial_device

# Function launching a script and keeping the serial connected device updated about it's state
def doAction(serial_device, script_to_run):
    # Launching the script
    script_process = subprocess.Popen(
        ['bash', script_to_run], 
        stdout=subprocess.PIPE, 
        text=True
    )
    logging.warning(script_to_run + " now starting")

    backup_is_done = False
    last_serialwrite_epoch_time = 0

    # Keep sending informations to serial connected device until script execution is done
    while backup_is_done == False:
        last_stdout_line = ""

        # Check if script execution has ended or not
        if script_process.poll() is None: 
            # Still running
            last_stdout_line = script_process.stdout.readline()
            # Wait at least half a second between serial writes
            epoch_time = time.time()
            if epoch_time > last_serialwrite_epoch_time + 0.5 :
                # Extracting reconstruction speed, elapsed time on current file, current file number, remaining files to check
                pattern = r"(\d{1,3},\d{2}.B\/s).*(\d{1,2}:\d{2}:\d{2}).*xfr#(\d{1,30}).*(\d{1,30}\/\d{1,30})"
                match = re.search(pattern, last_stdout_line)
                if match:
                    # Send data to display to the serial connected device as a single string
                    serializedLogLine = match.group(1) + "_" + match.group(2) + "_" + match.group(3) + "_" + match.group(4)
                    sendMessage(
                        serial_device, 
                        SHOW_DATA, 
                        serializedLogLine
                    ) 
                    last_serialwrite_epoch_time = epoch_time
        else:
            # Tell the serial connected device the script execution is over
            logging.warning(script_to_run + " execution has ended, sending end signal to ESP32")
            sendMessage(serial_device, END_OF_TASK, "")
            backup_is_done = True

##############################################
# Loop
##############################################

logging.warning("Script started, searching for configuration file: " + CONFIG_FILE_PATH)
data = configFileLoader()

script_to_run = data.get('script_to_run')
esp32_pid = data.get('esp32_product_id')
esp32_vid = data.get('esp32_vendor_id')

logging.warning("Config file found! Script to run is " + script_to_run + ". Now searching for a device with a product ID matching " + str(esp32_pid) + " and a vendor ID matching " + str(esp32_vid))

serial_device = None

while True: 
    if serial_device == None:
        # ESP32 does a serial write at boot, waiting for it to finish before first serial read
        time.sleep(1)
        # No device connected, waiting 4 more seconds before next scan
        serial_device = findDeviceByPidVid(esp32_pid, esp32_vid)
        if serial_device == None:
            time.sleep(4)
    else:
        try:
            # Still connected : wait for an instruction to be given on the serial interface
            if serial_device.isOpen():
                input_data = serial_device.readline().strip().decode("utf-8")
                logging.warning("Received serial message : " + input_data)

                if DO_ACTION in input_data:
                    # DO_ACTION order received, doing said action
                    logging.warning("DO_ACTION instruction detected")
                    doAction(serial_device, script_to_run)
                else:
                    logging.warning("Serial message has no known meaning, ignoring")
        except serial.SerialException:
            # Device not connected anymore, reseting stored values about the device
            logging.warning("Can't reach device anymore, assuming it was disconnected. Will continue to search for it.")
            device_port = None
            serial_device = None
                
