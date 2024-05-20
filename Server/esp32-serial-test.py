# Importing Libraries 
import serial 
import time 

serialDevice = serial.Serial(port='/dev/ttyACM0', baudrate=115200, timeout=.1) 

def write(): 
    serialDevice.write(bytes("1-SHOWDATA=", 'utf-8')) 
    time.sleep(0.05) 

while True: 
    input("Press enter to write 1-SHOWDATA to /dev/ttyACM0")
    write()
