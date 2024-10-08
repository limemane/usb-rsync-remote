# This is an example of what your rsync launch script should look like.
# The rsync sommand below is the one I use to backup file from my home server to a ExFAT Hard drive. Tune it to match your own needs :)

# Mount external usb drive where files will be backed up
sudo mount /dev/your/device /media/mount/device/here

# Check if usb drive is mounted
if ! mountpoint -q /media/mount/device/here ; then
  echo "USB drive was NOT mounted, stopping script execution"
  exit 1
fi

# Delete previous log file
sudo rm -f /your/logs/path

# Do the backup
sudo rsync -hrltDR --delete --modify-window=1 --info=progress2 --log-file=/your/logs/path path/to/folder/to/backup path/to/other/folder/to/backup path/to/backup/destination 

# Writes any data buffered in memory out to disk
sync

# Unmount external usb drive
sudo umount /dev/sdc2