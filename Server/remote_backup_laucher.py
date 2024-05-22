# Importing Libraries 
import serial 
import time 
import subprocess
import logging

serial_device = serial.Serial(port='/dev/ttyACM0', baudrate=115200, timeout=.1) 

def sendMessage(message_content): 
    serial_device.write(bytes("1-SHOWDATA=" + message_content, 'utf-8')) 
    time.sleep(0.05) 

#result = subprocess.run(['bash', './test/fake-script-output-small.sh'], stdout=subprocess.PIPE)

p = subprocess.Popen(['bash', './test/fake-script-output-small.sh'], stdout=subprocess.PIPE, text=True)

while True: 
    
    last_stdout_line = ""
    last_serialwrite_epoch_time = 0

    # Returns the return code of the command. None if it hasn't finished
    if p.poll() is None: 
        # Still running
        last_stdout_line = p.stdout.readline()

        # Wait at least two second between to serial writes
        epoch_time = int(time.time())
        if epoch_time > last_serialwrite_epoch_time + 1 :
            logging.warning(last_stdout_line)
            sendMessage(last_stdout_line) 
    else:
        # Has finished
        time.sleep(1);
        sendMessage("2-ENDOFTASK=")

