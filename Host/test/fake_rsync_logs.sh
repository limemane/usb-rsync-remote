# rsync log output simulation, with random delays between log lines

# the real rsync command I use to backup my things looks like this
# sudo rsync -hrltDR --delete --modify-window=1 --info=progress2 --log-file=/path/to/optional/log/file path/to/folder/to/backup path/to/other/folder/to/backup path/to/backup/destination 

echo "              0   0%    0,00kB/s    0:00:00 (xfr#1, ir-chk=1046/1049)"
sleep 1
echo "              0   0%    0,00kB/s    0:00:00 (xfr#1, ir-chk=1034/1049)"
sleep .5 
echo "          7,61K   0%    0,00kB/s    0:00:00  "
sleep .5 
echo "          7,61K   0%    0,00kB/s    0:00:00 (xfr#2, ir-chk=1045/1049)"
sleep .5 
echo "        298,43K   0%  138,67MB/s    0:00:00 (xfr#3, ir-chk=1009/1054)"
sleep .5 
echo "          5,23M   2%   59,96MB/s    0:00:00 (xfr#4, ir-chk=1104/1461)"
sleep .001 
echo "          5,23M   2%   59,96MB/s    0:00:00 (xfr#4, ir-chk=1011/1461)"
sleep .001 
echo "          5,23M   2%   59,96MB/s    0:00:00 (xfr#4, ir-chk=1011/1461)"
sleep .001 
echo "          5,23M   2%   59,96MB/s    0:00:00 (xfr#4, ir-chk=1011/1461)"
sleep .001 
echo "          5,23M   2%   59,96MB/s    0:00:00 (xfr#4, ir-chk=1011/1461)"
sleep .001 
echo "          5,23M   2%   59,96MB/s    0:00:00 (xfr#4, ir-chk=1011/1461)"
sleep .001 
echo "          5,23M   2%   59,96MB/s    0:00:00 (xfr#4, ir-chk=1011/1461)"
sleep .001 
echo "          5,23M   2%   59,96MB/s    0:00:00 (xfr#4, ir-chk=1011/1461)"
sleep .001 
echo "          5,23M   0%   27,79kB/s    0:03:03 (xfr#4, to-chk=106/163373)"
sleep .001 
echo "          5,23M   0%   27,79kB/s    0:03:03 (xfr#4, to-chk=76/163373) "
sleep .001 
echo "          5,23M   0%   27,79kB/s    0:03:03 (xfr#4, to-chk=65/163373)"
sleep .001 
echo "          5,23M   0%   27,79kB/s    0:03:03 (xfr#4, to-chk=53/163373)"
sleep .5 
echo "          5,23M   0%   27,79kB/s    0:03:03 (xfr#4, to-chk=51/163373)"
sleep .5 
echo "          5,23M   0%   27,79kB/s    0:03:03 (xfr#4, to-chk=48/163373)"
sleep .5 
echo "          5,23M   0%   27,79kB/s    0:03:03 (xfr#4, to-chk=38/163373)"
sleep .5 
echo "          5,23M   0%   27,79kB/s    0:03:03 (xfr#4, to-chk=28/163373)"
sleep 2
echo "          5,23M   0%   27,79kB/s    0:03:03 (xfr#4, to-chk=18/163373)"
sleep 1 
echo "          5,23M   0%   27,79kB/s    0:03:03 (xfr#4, to-chk=0/163373) "
sleep .001 
echo "          5,23M   0%   27,79kB/s    0:03:03 (xfr#4, to-chk=0/163373)"
