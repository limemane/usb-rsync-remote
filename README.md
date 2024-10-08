# USB rsync remote

A USB remote with a push button and a small OLED display for Linux/macOS.

The intended usage of this remote is to start a rsync backup when the button is pressed, and to display rsync logs data on the OLED display while rsync is running.

A small Python script has to run on the computer where the remote is plugged to make it work properly. 

## Hardware involved

- 1x ESP32
- 1x OLED SSD1306 I2C display (SCL pin 22, SDA pin 21)
- 1x Push button (pin 25)
- Any computer able to run a Python script

## Setup

- Get Python 3+ installed
- Put the `Host` folder on your computer
- Install required librairies `pip install -r Host/requirements.txt`
- Open the config file `Host/src/config.yaml` and 
  - Set the path to the bash script you want the remote to launch
  - Set you ESP32 serial id https://github.com/turbojonquille/usb-script-launcher/blob/main/Host/README.md
- Connect you ESP32 to the computer and using VScode and Platform.io compile and upload `ESP32` content to your ESP32.
- Start the python script `sudo python3 Host/src/usb_remote_listener.py`.
- "Ready to start" should appear on the remote OLED display after a short while.
- Press the push button. The script you set in the config file should now start.

