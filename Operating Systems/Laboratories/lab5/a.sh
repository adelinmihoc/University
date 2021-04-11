#!/bin/bash

CMD=""
ARG=""
for C in $*; do
	if [ "$C" == ";"  ]; then
		if [ -n "$CMD"  ]; then
			$CMD $ARG
		fi
		CMD=""
		ARG=""
	elif [ -z "$CMD"  ]; then
		cmd = $C
	else
		ARG="$ARG $C"
	fi
done

if [ -n "$CMD" ]; then
       $CMD $ARG
fi       
