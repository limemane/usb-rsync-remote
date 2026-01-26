# USB rsync remote

<p  align="center">
<img src="https://github.com/limemane/usb-rsync-remote/blob/main/usbRemote.png"/>
</p>

A USB remote with a display. Its role is to trigger a rsync backup after pressing a button, display live informations from rsync logs on the screen and finally show a message when the rsync task is done.

### Use case

Personally I'm using this to trigger a backup from my home server to an external drive on the go, without needing to power on another computer. I know this could also be achieved by making a script to start a backup directly when plugging an external drive, but I wanted to get some data and also a clear confirmation that rsync was done and my drive unmounted before actually unplugging it, so I came to this solution ! 

### How does it works 

A light Python script has to run on the computer where the remote is plugged.
When the USB remote button is pressed, a serial command is sent to the computer.
As soon as the command is read by the Python script, it starts the bash script containing the rsync command of your choice, and rsync logs are then formatted and sent to the USB remote.

### Hardware involved

- 1x ESP32
- 1x OLED SSD1306 I2C display (SCL pin 22, SDA pin 21)
- 1x Push button (pin 25)
- Any computer able to run a Python script

# Getting started

First, clone this repo on your computer `git clone https://github.com/limemane/usb-rsync-remote.git`

### Step 1: Get your ESP32 ready
- Using VSCode, install the Platform.io extension
- Connect your ESP32 to your computer
- Using VScode and Platform.io, open the ESP32 folder then compile and upload the firmware to the ESP32.

### Step 2: Get your computer ready
- Install Python 3+
- Install the required Python librairies `pip3 install -r Host/requirements.txt`
- Open the config file `Host/config.yaml` and :
  - Set the path to the bash script containing your rsync command. See https://github.com/limemane/usb-rsync-remote/blob/main/Host/example/rsync_start_script.sh
  - Set you ESP32 VID/PID. See https://github.com/limemane/usb-rsync-remote/blob/main/Host/README.md
- Start the Python script as root `sudo python3 Host/usb_remote_listener.py`.

### Step 3: Profit!
- Now that your ESP32 contains the right firmware and you computer also runs the remote listener script, "Ready to start" should appear on the ESP32 OLED display as soon as you plug it in.
- Press the push button on the remote. The bash script you set in the config file should now start and rsync logs shloud be displayed on the ESP32 OLED display.

### Step 4: Start listener on computer startup (GNU/Linux)
- If you want usb_remote_listener.py to start automaticaly, copy the following service file (see https://github.com/limemane/usb-rsync-remote/blob/main/Host/example/usb-rsync-remote.service) into `/etc/systemd/system`. Don't forget to set your own WorkingDirectory path.
- Get systemd to read the newly created service file with `sudo systemctl daemon-reload`
- Enable the service `sudo systemctl enable usb-rsync-remote.service`
- Reboot your computer. The script should now run on startup.
- To check the service state and the logs you can use `sudo systemctl status usb-rsync-remote`
