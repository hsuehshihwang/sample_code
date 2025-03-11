#!/bin/bash
make clean
make
echo "original sample =========>"
./sample
echo "hijack rand =========>"
LD_PRELOAD=./urandom.so ./sample
echo "hijack printf =========>"
LD_PRELOAD=./uprintf.so ./sample
