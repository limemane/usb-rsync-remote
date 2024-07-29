# USB script launcher

A crossplatform USB remote with a push button and a small OLED display. 

Pushing the button allows you to start any script you set up on the computer where you plugged the remote (aka "host machine"). 
The host machine can also send informations back to the remote display to track the script execution.

## Hardware involved

- An ESP32
- An OLED SSD1306 display
- One push button 
- A computer able to run a Python script

## Electronic diagram

- Todo

## Setup

### Host machine

- Get Python 3+ with pyserial installed on the host machine
  - Use `pip3 install pyserial` to get pyserial after installing Python
- Put the `Host` folder on your host machine
- Open the config file `Host/src/config.yaml` and
  - Set the path to the script you want the remote to launch
  - Set you ESP32 serial id https://github.com/turbojonquille/usb-script-launcher/blob/main/Host/README.md
- You can now start the host script `Host/src/usb_remote_listener.py`.

### Remote

- Using VScode and Platform.io, compile and upload `ESP32` content to your ESP32.
- You can now plug it in the host machine and press the button !

