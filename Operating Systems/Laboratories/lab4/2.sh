#!/bin/bash

sed 's/\(\([a-z][0-9]\)\+\)/\n\1\n/gi' 2.txt |\
grep '\([a-zA-Z][0-9]\)' |\
sed 's/[a-z]/ /g' |\
awk -f 2.awk
