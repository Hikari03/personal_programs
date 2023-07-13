#!/bin/bash

while :
do
    sleep 300
    TEMP="$("$HOME/rpi-examples/LM75A/bash/lm75a.sh")"
    if [[ -z "$var" ]]; then
      continue
    fi
    RES=$TEMP
    RES+='°C'
    echo "$RES" > ~/FTP/share/www/assets/temperature.txt
    echo "$(date +"%F %R");$RES" >> ~/temperature-plot.txt
   
done
