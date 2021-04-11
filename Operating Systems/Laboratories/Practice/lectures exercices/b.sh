#!/bin/bash
echo Command: $0
echo First fourargs: $1 $2 $3 $4
echoAll args: $@
echo Arg count: $#
true
echo Command true
exited with code $?
false
echo Command false exited with code $?
