#!/bin/bash

# 5. Write a script that extracts from all the C source files given as command line arguments the included libraries and saves them in a file.

while [ $# -gt 0 ]; do
  file=$1
  # echo "$file"
  $(touch libraries.txt)
  if [ $(echo "$file" | grep "\.c$" | wc -l) -eq 1 ] && [ -f "$file" ]; then
    $(echo "$file" >> "libraries.txt")
    $(echo "$(cat "$file" | grep "^#include")" >> "libraries.txt")
    $(echo "" >> "libraries.txt")
  fi
  shift 1
done
