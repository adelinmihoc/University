#!/bin/bash

# Write a shell script that will show on the screen every s seconds, a top of the 
# first n users on the linux system, sorted by the number their running 
# processes (n will be read from keyboard and s from command line).

sec=$1
num=$2

if [ "$sec" == "" ] ||  [ $(echo "$sec" | grep "[^0-9]\+") ]; then
  echo "not a number"
  exit 0
fi

while true; do
  clear
  ps aux | awk '{print $1}' | sort | uniq -c | sort -n -r | head -n $num
  sleep $sec
done
