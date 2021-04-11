#!/bin/bash

# Afisati numele fisierelor dintr-un director dat ca parametru
# care contin peste 5 cifre

find $1 -type f | while read F; do
  nrl=`cat $F | grep "[1-9][0-9][0-9][0-9][0-9]" | wc -l`
  if [ $nrl -ge 1 ]; then
    echo $F
  fi
done
