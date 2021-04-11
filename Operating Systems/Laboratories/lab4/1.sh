#!/bin/bash


find a -type f -exec ls -l {} \; |\
	awk '{print $5}' |\
	sort -n |\
	head -n -1 |\
	tail -n +2 |\
	awk '{n = n + $1} END{print (n / NR)}'
