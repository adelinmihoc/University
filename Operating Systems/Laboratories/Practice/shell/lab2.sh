#!/bin/bash

# Afișați numele fișierelor dintr-un director dat ca parametru care conțin numere de peste 5 cifre.

dire=$1

for file in $(find "$dire"); do
  echo "$file" | grep "[0-9]\{5\}"
done
