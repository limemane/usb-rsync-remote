# USB rsync remote

A USB remote with a push button and a small OLED display for Linux/macOS.

The intended usage of this remote is to start a rsync backup when the button is pressed, and to display rsync logs data on the OLED display while rsync is running. Great for headless servers !

A small Python script has to run on the computer where the remote is plugged to make it work properly. 

## Hardware involved

- 1x ESP32
- 1x OLED SSD1306 I2C display (SCL pin 22, SDA pin 21)
- 1x Push button (pin 25)
- Any computer able to run a Python script

## How to install

- Get Python 3+ installed
- Put the `Host` folder on your computer
- Install required librairies `pip install -r Host/requirements.txt`
- Open the config file `Host/src/config.yaml` and 
  - Set the path to the bash script containing your rsync command (see https://github.com/limemane/usb-rsync-remote/blob/main/Host/example/rsync_start_script.sh)
  - Set you ESP32 serial id https://github.com/limemane/usb-rsync-remote/blob/main/Host/README.md
- Connect you ESP32 to the computer and using VScode and Platform.io compile and upload `ESP32` content to your ESP32.
- Start the python script as root `sudo python3 Host/src/usb_remote_listener.py`.
- "Ready to start" should appear on the remote OLED display after a short while.
- Press the push button. The script you set in the config file should now start !

## Going further

In order to make the remote work as intended you will also need to run the Python script automatically on startup. To make it so on GNU/Linux you should use systemd as described :
- Copy the service file (see https://github.com/limemane/usb-rsync-remote/blob/main/Host/example/usb-rsync-remote.service) into `/etc/systemd/system`. Don't forget to update WorkingDirectory path or it will not work !
- Get systemd to read the newly created service file with `sudo systemctl daemon-reload`
- Enable the service `sudo systemctl enable usb-rsync-remote.service`
- Reboot. The script should now start on startup.
- To check the service state and the logs you can use `sudo systemctl status usb-rsync-remote`
