# USB rsync remote

<p  align="center">
<img src="https://github.com/limemane/usb-rsync-remote/blob/main/usbRemote.png"/>
</p>

A USB remote with a display, used to start a rsync backup when its button is pressed. It will display rsync logs data on its OLED display while rsync is running. 
Great for headless home servers !

### How does it works 

A small Python script has to run on the computer where the remote is plugged.
When the USB remote button is pressed, a serial command is sent to the computer.
As soon as the command is read by the Python script, a bash script containing the rsync command of your choice is started by the Python script, and rsync logs are then formatted and sent to the USB remote.

### Hardware involved

- 1x ESP32
- 1x OLED SSD1306 I2C display (SCL pin 22, SDA pin 21)
- 1x Push button (pin 25)
- Any computer able to run a Python script

# Getting started

First, clone this repo on your computer `git clone https://github.com/limemane/usb-rsync-remote.git`

### Step 1: Get your ESP32 ready
- Using VSCode, install Platform.io extension
- Connect your ESP32 to your computer
- On VScode, Open Folder... > ESP32 then using Platform.io compile and upload the project to the ESP32.

### Step 2: Get your computer ready
- Install Python 3+
- Install required Python librairies `pip3 install -r Host/requirements.txt`
- Open the config file `Host/config.yaml` and 
  - Set the path to the bash script containing your rsync command. See https://github.com/limemane/usb-rsync-remote/blob/main/Host/example/rsync_start_script.sh
  - Set you ESP32 VID/PID. See https://github.com/limemane/usb-rsync-remote/blob/main/Host/README.md
- Start the python script as root `sudo python3 Host/usb_remote_listener.py`.

### Step 3: Profit!
- Now that your ESP32 contains the right firmware and you computer also runs the remote listener script, "Ready to start" should appear on the ESP32 OLED display as soon as you plug it in.
- Press the push button. The script you set in the config file should now start and rsync logs shloud also be displayed on the ESP32 OLED display

### Step 4: Start listener on computer startup (GNU/Linux)
- If you also want usb_remote_listener.py to start automaticaly, copy the following service file (see https://github.com/limemane/usb-rsync-remote/blob/main/Host/example/usb-rsync-remote.service) into `/etc/systemd/system`. Don't forget to set your own WorkingDirectory path.
- Get systemd to read the newly created service file with `sudo systemctl daemon-reload`
- Enable the service `sudo systemctl enable usb-rsync-remote.service`
- Reboot. The script should now start on startup.
- To check the service state and the logs you can use `sudo systemctl status usb-rsync-remote`
