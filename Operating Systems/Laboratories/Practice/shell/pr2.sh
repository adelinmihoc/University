#!/bin/bash

#3. Write a script that receives as command line arguments pairs consisting of a filename and a word. 
# For each pair, check if the given word appears at least 3 times in the file and print a corresponding message.

while [ $# -gt 1 ]; do

  file_name=$1
  word=$2

  if [ $(cat "$file_name" | grep -c "$word") -ge 3 ]; then
    echo "da bai apare"

  else 
    echo "nu ba ceai"

  fi

  shift 2

done



