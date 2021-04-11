#!/bin/bash

# Find recursively in a directory, all the files with the extension ".log" 
# and sort their lines (replace the original file with the sorted content).

find dir -type f -name "*.log" | while read -r file;do
  sort -o "$file" "$file"
done


