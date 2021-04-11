#!/bin/bash

for F in /usr/bin/*; do
	T=`file -b $F`
	if echo $T | grep -q -v "^ELF "; then
		echo $F
	fi
done 
