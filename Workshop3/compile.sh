#!/bin/bash

if [ -z "$fn" ]
then
	echo "Please input source filename without suffix"
	echo "usage: fn=<filename> ./compile.sh"
else
	gcc  -Wall -fopenmp -std=c99 -pthread ${fn}.c -o $fn.o
fi

unset $fn
