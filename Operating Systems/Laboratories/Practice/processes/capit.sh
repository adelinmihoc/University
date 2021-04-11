#!/bin/bash

sed "s/\<\([a-z]\)/\u\1/g" $1 > ${1}_temp
