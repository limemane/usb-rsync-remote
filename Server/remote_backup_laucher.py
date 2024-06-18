import serial 
import serial.tools.list_ports
import time 
import subprocess
import logging

################
#
# Constants
#
################

# Instructions
CONNECTION_OK = "-CONNOK="
DO_ACTION = "-DOACTION="
SHOW_DATA = "-SHOWDATA="
END_OF_TASK = "-ENDOFTASK="

# Serial parameters
ESP32_SERIAL = "5185008510"
BAUD_RATE = 115200

SCRIPT_TO_LAUNCH = "./test/fake-script-output-small.sh"

################
#
# Functions
#
################

# Sends a message to the serial connected device
def sendMessage(serial_device, message_type, message_content): 
    serial_device.write(bytes(message_type + message_content, 'utf-8')) 
    time.sleep(0.05) 

# Given the serial number a of device, return its port if device found
def searchDevicePortBySerialNumber(serial_number):
    device_port_found = None
    # Scanning serial ports waiting for the right serial number
    for port in serial.tools.list_ports.comports():
        if port.serial_number == serial_number:
            # Device found, store its port and break loop
            logging.warning(f"Port found: {port} - Serial: {port.serial_number}")
            device_port_found = port.device
            break

    return device_port_found

# Launches a script and keeps the serial connected device updated about it's state
def doAction(serial_device):
    # Launching the script
    script_process = subprocess.Popen(['bash', SCRIPT_TO_LAUNCH], stdout=subprocess.PIPE, text=True)
    logging.warning(SCRIPT_TO_LAUNCH + " now starting")

    backup_is_done = False;

    # Keep sending informations to serial connected device until script execution is done
    while backup_is_done == False:
        last_stdout_line = ""
        last_serialwrite_epoch_time = 0

        # Check if scirpt execution ened or not
        if script_process.poll() is None: 
            # Still running
            last_stdout_line = script_process.stdout.readline()
            # Wait at least one second between serial writes
            epoch_time = int(time.time())
            if epoch_time > last_serialwrite_epoch_time :
                # Send data to display to the serial connected device
                sendMessage(serial_device, SHOW_DATA, last_stdout_line) 
                last_serialwrite_epoch_time = epoch_time
        else:
            # Tell the serial connected device the script execution is over
            logging.warning(SCRIPT_TO_LAUNCH + " execution has ended, sending signal to ESP32")
            sendMessage(serial_device, END_OF_TASK, "")
            backup_is_done = True

################
#
# Loop
#
################

logging.warning("Script started, searching for a device with a serial number matching " + ESP32_SERIAL)

device_port = None
serial_device = None

while True: 
    if device_port == None:
        # No device connected, searching for it on a 5 seconds interval
        device_port = searchDevicePortBySerialNumber(ESP32_SERIAL)
        time.sleep(5)
    else:
        if serial_device == None:
            # Device found, initialize serial interface
            serial_device = serial.Serial(port=device_port, baudrate=BAUD_RATE, timeout=None) 
            sendMessage(serial_device, CONNECTION_OK, "") 
        else:
            # Device has already been initialized, checking it is still connected
            if searchDevicePortBySerialNumber(ESP32_SERIAL) != None:
                # Still connected : wait for an instruction to be given on the serial interface
                if serial_device.isOpen():
                    input_data = serial_device.readline().strip().decode("utf-8")
                    logging.warning("Received serial message : " + input_data)

                    if DO_ACTION in input_data:
                        # DO_ACTION order received, doing said action
                        logging.warning("DO_ACTION instruction detected")
                        doAction(serial_device)
                    else:
                        logging.warning("Serial message has no known meaning, ignoring")
                else:
                    # Device not connected anymore, resetting stored values about the device
                    # TODO : An exception is triggered before this can happen, must find an other way to detect disconnected device
                    logging.warning("Device disconnected")
                    device_port = None
                    serial_device = None
