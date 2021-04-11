#!/bin/bash

# 4. Sort all files given as command line arguments descending by size.

n=0 # length of array
while [ $# -gt 0 ]; do # reading and putting in an array space and file name
  if [ -f "$1" ]; then
    array[$n]="$(du "$1")"
    n=$((n+1))
  fi
  shift 1
done



# sorting
n=$((n-1)) # decrement to last element
for i in $(seq 0 $n); do
   aux="$aux"$'\n'"${array[i]}"
#  echo "${array[i]}"
done

echo "$aux" | sort -n
