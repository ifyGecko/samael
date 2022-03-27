#!/bin/bash

# get the number of 0xCC's from the text segment of samael
cc_count=$(objdump -s -j .init samael | grep cc | cut -c 7- | cut -c -36 | tr -d "[:blank:]" | \
               sed 's/.\{2\}/& /g' | sed -n '/cc/p' | grep -o "cc" | wc -l)

cc_count=$(($cc_count + $(objdump -s -j .plt samael | grep cc | cut -c 7- | cut -c -36 | tr -d "[:blank:]" | \
                              sed 's/.\{2\}/& /g' | sed -n '/cc/p' | grep -o "cc" | wc -l)))

cc_count=$(($cc_count + $(objdump -s -j .plt.got samael | grep cc | cut -c 7- | cut -c -36 | tr -d "[:blank:]" | \
                              sed 's/.\{2\}/& /g' | sed -n '/cc/p' | grep -o "cc" | wc -l)))

cc_count=$(($cc_count + $(objdump -s -j .text samael | grep cc | cut -c 7- | cut -c -36 | tr -d "[:blank:]" | \
                              sed 's/.\{2\}/& /g' | sed -n '/cc/p' | grep -o "cc" | wc -l)))

cc_count=$(($cc_count + $(objdump -s -j .fini samael | grep cc | cut -c 7- | cut -c -36 | tr -d "[:blank:]" | \
                              sed 's/.\{2\}/& /g' | sed -n '/cc/p' | grep -o "cc" | wc -l)))


# place this number in the correct macro definition to know how many 0xCC's should be present
sed -i 's/#define count [0-9]/#define count '$cc_count'/g' samael.h
