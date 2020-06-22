#!/bin/bash

num=$(objdump -s -j .text samael | grep cc | cut -c 7- | sed -n '/cc/p' | wc -l)

sed -i 's/#define count [0-9]/#define count '$num'/g' ../tools/anti-debug/anti-debug.h
