import serial 
import time 
import subprocess
import logging

################
#
# Constants
#
################

DO_ACTION = "0-DOACTION="
SHOW_DATA = "1-SHOWDATA="
END_OF_TASK = "2-ENDOFTASK="

SCRIPT_TO_LAUNCH = "./test/fake-script-output-small.sh"

################
#
# Init
#
################

# Initialize serial interface
serial_device = serial.Serial(port='/dev/ttyACM0', baudrate=115200, timeout=.1) 

################
#
# Functions
#
################

# Sends a message to make the ESP32 display data
def sendDisplayMessage(message_content): 
    serial_device.write(bytes(SHOW_DATA + message_content, 'utf-8')) 
    time.sleep(0.05) 

# Sends a message to make the ESP32 aware that script execution has ended
def sendEndOfTaskMessage(message_content): 
    serial_device.write(bytes(END_OF_TASK + message_content, 'utf-8')) 
    time.sleep(0.05) 

# Launches a script and keeps the ESP32 updated about it's state
def doAction():
    # Launching the script
    script_process = subprocess.Popen(['bash', SCRIPT_TO_LAUNCH], stdout=subprocess.PIPE, text=True)
    logging.warning(SCRIPT_TO_LAUNCH + " now starting")

    backup_is_done = False;

    # Keep sending informations to ESP32 until script execution is done
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
                sendDisplayMessage(last_stdout_line) 
                last_serialwrite_epoch_time = epoch_time
        else:
            # Has finished
            time.sleep(1);
            logging.warning(SCRIPT_TO_LAUNCH + " execution has ended, sending signal to ESP32")
            sendEndOfTaskMessage("")
            backup_is_done = True

################
#
# Loop
#
################

while True: 

    # Wait for an instruction to be given on the serial interface
    if serial_device.isOpen():
        
        input_data = serial_device.readline().strip().decode("utf-8")
        logging.warning("Received serial message : " + input_data)

        if DO_ACTION in input_data:
            # DO_ACTION order received, doing said action
            logging.warning("DO_ACTION instruction detected")
            doAction()
        else:
            logging.warning("Serial message has no meaning, ignoring")
    
    time.sleep(1)