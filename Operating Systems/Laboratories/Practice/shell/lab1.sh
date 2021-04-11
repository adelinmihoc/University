#!/bin/bash

# Calculați numărul mediu de linii din fișierele text dintr-un director dat ca parametru (comenzi: find, file, wc).

dir=$1

no_files=0
no_lines=0
for file in $(find $dir ); do
  is_text=$(file -b "$file" | grep -c "text")
  if [ $is_text -eq 1 ]; then
    lines=$(cat $file | wc -l)
    no_lines=$(($no_lines + $lines))
    no_files=$(($no_files + 1))
    # echo "$no_lines $no_files"
  fi
done

echo $((no_lines / no_files))
