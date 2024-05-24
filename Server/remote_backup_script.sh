# Mount external usb drive where files will be backed up
echo "Mounting /dev/sc2 in /media/usb-drive"
sudo mount /dev/sdc2 /media/usb-drive

# Delete previous log file
sudo rm -f /home/folfman/backup-rsync.log

# Do the backup
sudo rsync -hrvltDR --delete --modify-window=1 --stats --info=progress2 --log-file=/home/folfman/backup-rsync.log /dockerzone/ /mnt/internalDriveBay/ /media/usb-drive/server_backup/ 
echo

# Unmount external usb drive
echo "Trying to unmount /dev/sc2"
sudo umount /dev/sdc2
