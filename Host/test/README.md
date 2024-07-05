# Testing serial communication on windows using WSL

If you intend to use this project to run a bash script but want to test it on a Windows machine before, a WSL GNU/Linux distribution has to be installed along with usbipd.
Then the ESP32 bus has to be shared to the WSL-hosted OS.


## Sharing ESP32 bus to a WSL-hosted OS 

Open a terminal on your Windows then type :

`usbipd list` to get the ESP32 BUSID

`usbipd bind --busid 1-2` to share the BUSID (requires administrator privileges)

`usbipd attach --wsl --busid 1-2` to attach the ESP32 to the WSL-hosted OS

`usbipd detach --busid 1-2` to make the ESP32 available on Windows again

To check if the newly shared ESP32 is detected type `lsusb` in the WSL-hoted GNU/Linux terminal to get the device ID.


## Testing data exchanges with ESP32

### Using Bash

Type `stty 115200 -F /dev/ttyACM0 raw -echo` on the WSL-hosted GNU/Linux to start the serial communication.

`cat /dev/ttyACM0` can be used to show messages sent by the ESP32

To send a message to the ESP32 use `echo "message to send" > /dev/ttyACM0`


### Using Python

see test/esp32-serial-test.py
