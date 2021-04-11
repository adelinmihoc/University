#!/bin/bash


# Find recursively in a directory all ".c" files having more than 500 lines. Stop after finding 2 such files.


files_found=0
find dir -type f -name "*.c" | while read file;do
  if [ $files_found -ge 2 ];then
    break
  fi
  line=$(wc -l $file | awk '{print $1}')
  if [ $line -ge 500 ];then
    echo "$file"
    files_found=$(($files_found + 1))
  fi
done
