# Importing Libraries 
import serial 
import time 

serialDevice = serial.Serial(port='/dev/ttyACM0', baudrate=115200, timeout=.1) 

def sendMessage(messageContent): 
    serialDevice.write(bytes("1-SHOWDATA=" + messageContent, 'utf-8')) 
    time.sleep(0.05) 

while True: 
    messageContent = input("Write something to send to /dev/ttyACM0 : ")
    sendMessage(messageContent)
