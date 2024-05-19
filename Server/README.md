# Testing serial communication on windows using WSL

This project is intended to run on GNU/Linux exclusively.
To test the whole project easily using a Windows machine, a WSL GNU/Linux distribution has to be installed along with usbipd.

Then the ESP32 bus has to be shared to the WSL-hosted OS :

`usbipd list` to get the ESP32 BUSID

`usbipd bind --busid 1-2` to share the BUSID (requires administrator privileges)

`usbipd attach --wsl --busid 1-2` to attach the ESP32 to the WSL-hosted OS

`usbipd detach --busid 1-2` to make the ESP32 available on Windows again

Type `lsusb` in the WSL-hoted GNU/Linux terminal to get the device ID.