# Mount external usb drive where files will be backed up
sudo mount /dev/sdc2 /media/usb-drive

# Delete previous log file
sudo rm -f /home/folfman/backup-rsync.log

# Do the backup
sudo rsync -hrltDR --delete --modify-window=1 --info=progress2 --log-file=/home/folfman/backup-rsync.log /dockerzone/ /mnt/internalDriveBay/ /media/usb-drive/server_backup/ 

# Unmount external usb drive
sudo umount /dev/sdc2
