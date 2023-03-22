
#!/bin/bash
#sudo stty speed 115200

sudo stty -F /dev/ttyUSB0 speed 115200
#od -x < /dev/ttyUSB0
cat /dev/ttyUSB0

#echo Serial Speed set to 115200
