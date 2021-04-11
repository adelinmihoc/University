#!/bin/bash

nrFound = 0;

for file in $(find dir | grep "\.c$"); do
	nrLines=$(cat "$file" | wc -l)
	if [ $nrLines -gt 500 ]; then
		nrFound=$(($nrFound + 1))
		echo "$file"
	fi
	if [ $nrFound -ge 2 ]; then
		exit 0
	fi
done
