#!/bin/bash

str=$1
bf_str=''

for (( i=0; i<${#str}; i++ )); do
    dec=$(echo "${str:$i:1}" | hexdump -v -e '/1 "%02d\n"' | head -n 1)
    for (( j=0; j<dec; j++ )); do
	bf_str+='+'
    done
    bf_str+='>'
done

echo $bf_str
