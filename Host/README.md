# Host script

To allow the ESP32 USB remote to start, the following Python script `src/usb_remote_listener.py` must be running on the host machine.
A YAML config file is provided to allow the user to specifiy the path of the script to launch and the ESP32 device serial number. Both are mandatory.

## How do I find my ESP32 vendor ID and product ID

### GNU/Linux 
Open a terminal and type `lsusb -v`.
Search for the device corresponding to your ESP32

### macos
Open a terminal and type `ls /dev/tty* | grep usb`.

### Windows
Open the Device Manager, then unfold "Ports".
You should get a device with a COM port assigned to it. Show its properties then go into the details tab. 
