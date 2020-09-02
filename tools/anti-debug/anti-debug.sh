#!/bin/bash

# get the number of 0xCC's from the text section
x=$(objdump -s -j .text samael | grep cc | cut -c 9- | cut -c -35 | tr -d "[:blank:]" | \
    sed 's/.\{2\}/& /g' | sed -n '/cc/p' | grep -o "cc" | wc -l)

#get number of 0xCC's from the __libc_freeres_fn section
y=$(objdump -s -j __libc_freeres_fn samael | grep cc | cut -c 9- | cut -c -35 | tr -d "[:blank:]" | \
    sed 's/.\{2\}/& /g' | sed -n '/cc/p' | grep -o "cc" | wc -l)

# add to get total # of 0xCC's from .text up to .fini
z=$((x + y))

# place this number in the correct macro definition to know how many 0xCC's should be present
sed -i 's/#define count [0-9]/#define count '$z'/g' samael.h
