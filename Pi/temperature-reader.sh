#!/bin/bash

while :
do
    TEMP="$("/home/hikari/rpi-examples/LM75A/bash/lm75a.sh")"
    if [[ -z "$TEMP" ]]; then
      	echo "couldnt read temperature"
	continue
    fi
    RES=$TEMP
    RES+='°C'
    echo "$RES" > /home/hikari/FTP/share/www/assets/temperature.txt
    echo "$(date +"%F %R");$RES" >> /home/hikari/temperature-plot.txt
    sleep 300
done
