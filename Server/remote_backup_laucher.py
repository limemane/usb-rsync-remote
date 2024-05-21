# Importing Libraries 
import serial 
import time 
import subprocess
import logging

serialDevice = serial.Serial(port='/dev/ttyACM0', baudrate=115200, timeout=.1) 

def sendMessage(messageContent): 
    serialDevice.write(bytes("1-SHOWDATA=" + messageContent, 'utf-8')) 
    time.sleep(0.05) 

result = subprocess.run(['bash', './test/fake-script-output.sh'], stdout=subprocess.PIPE)

while True: 
    time.sleep(1);
    logging.warning(result.stdout.decode('utf-8'))
    sendMessage(result.stdout.decode('utf-8'))
