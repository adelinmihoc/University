#!/bin/bash

# Calculati numarul mediu de linii din fisierele text dintr-un director
# dat ca parametru (comenzi: find, file, wc)
nrl=0
cnt=0
find $1 -type f | while read F;do
  if file $F | grep -q "ASCII text"; then
    c=`cat $F | wc - l`
    nrl=$(($nrl+$c))
    cnt=$(($cnt+1))
  fi
done
echo $(($nrl/$cnt))
