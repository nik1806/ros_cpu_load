#!/bin/bash

file="./ros2_ws/cpu_load.log"

last_line=""

# continue reading file
while true;
do
    new_line=$(tail -n 1 "$file")
    # check if last line changes
    if [ "$new_line" != "$last_line" ]; then
        echo "CPU load: $new_line"
        # replace variable value
        last_line="$new_line"
    fi


done