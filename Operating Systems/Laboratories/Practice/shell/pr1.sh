#!/bin/bash

# 2. Write a script that reads filenames until the word "stop" is entered. For each filename, 
#    check if it is a text file and if it is, print the number of words on the first line.

while true; do
  read input 
  if [ "$input" == "stop" ]; then
    break;
  fi
  if [ -f "$input" ]; then
    is_text=$(file -b "$input" | grep -ic "text")
    if [ $is_text -eq 1 ]; then 
      echo "$input: $(head -n 1 "$input" | wc -w)"
    fi
  else 
    echo "$input is not a file "
  fi
done 
