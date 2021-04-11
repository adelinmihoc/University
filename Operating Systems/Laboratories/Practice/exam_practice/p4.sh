#!/bin/bash

# Find recursively in a given directory all the symbolic links
# report those that point to files/directories that no longer exist. 
# Use operator -L to test if a path is a symbolic link, 
# and operator -e to test if it exists (will return false if the target to wich the link points to dowsn't exist).


find dir -type l | while read F; do
  if [ ! -e $L ]; then
    echo $L points ot a file that no longer exists
  fi
  #echo fix bambucea
done
