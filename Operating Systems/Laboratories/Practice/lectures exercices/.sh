#!/bin/bah

echo Command: $0
echo First four args: $1 $2 $3 $4
echo All arguments: $@
echo Arguments count: $

true
echo Command true exited with code $?

false
echo Command false exited with code $?
