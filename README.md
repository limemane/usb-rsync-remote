# USB script launcher

A crossplatform USB remote with a push button and a small OLED display. 

Pushing the button allows you to start any bash script you set up on the computer where you plugged the remote. 
Said computer can also send back informations to the USB remote to display various data on the OLED screen.

## Hardware involved

- 1x ESP32
- 1x OLED SSD1306 display
- 1x push button 
- Any computer able to run a Python script

## Setup

### Computer

- Get Python 3+ installed on the host machine
- Put the `Host` folder on your host machine
- Install required librairies `pip install -r Host/requirements.txt`
- Open the config file `Host/src/config.yaml` and 
  - Set the path to the bash script you want the remote to launch
  - Set you ESP32 serial id https://github.com/turbojonquille/usb-script-launcher/blob/main/Host/README.md
- You can now start the host script `Host/src/usb_remote_listener.py`.

### USB Remote

- Using VScode and Platform.io, compile and upload `ESP32` content to your ESP32.
- You can now plug it in the host machine. "Ready to start" should appear on the remote OLED display after a short while.
- By pressing the push button your script should now start.

