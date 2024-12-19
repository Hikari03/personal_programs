#!/bin/sh

# prints all 8-bit colors with encoding

for color in {1..225}
    do echo -en "\033[38;5;${color}m38;5;${color} \n"
done | column -x

