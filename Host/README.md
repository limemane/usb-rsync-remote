# Host script

To allow the ESP32 USB remote to start, the following Python script `src/usb_remote_listener.py` must be running on the host machine.
A YAML config file is provided to allow the user to specifiy the path of the script to launch and the ESP32 device serial number. Both are mandatory.

## How do I find my ESP32 serial number

### macos
Open a terminal and type `ls /dev/tty* | grep usb`.
You should get something similar to `/dev/tty.usbserial-xxxx` where `xxxx` is your ESP32 serial number.
You can also use `system_profiler SPUSBDataType`.

### GNU/Linux 
Open a terminal and type `lsusb -v`.
Search for the device corresponding to your ESP32, then look for the `iSerial` property.

### Windows
Open the Device Manager. 
You should get a device with a COM port assigned to it. Show its properties then go into the details tab. 
Search for a property looking like `access path to device instance` or `device instance access path` (translated from a non-english OS, might be named differently).
The property value shows a path, your ESP32 serial number is located after the last `\` symbol. 
