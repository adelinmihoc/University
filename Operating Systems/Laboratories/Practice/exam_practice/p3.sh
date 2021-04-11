#!/bin/bash

# Find recursively in a directory, all the files with the extension ".log"
# ans sort their lines (repolace the original file with the sorted content).

find dir -type f | grep ".log$" | while read F; do
  cat $F | sort > $F

done
