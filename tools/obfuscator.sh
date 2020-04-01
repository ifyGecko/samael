#!/bin/bash

if [ -f "$1.bak" ]
then
    rm $1
else
    cat $1 > "$1.bak"
fi

counter=0
while read line; do
    counter=$(( counter + 1 ))
    if [ $counter -lt 32 ]
    then
	rand=$((0 + RANDOM % 3))
	if [[ $line =~ "(opt)" ]]
	then	    
	    line=${line/(opt)/"($rand)"}
	fi
    else
	if [[ $line =~ "{" ]] || [[ $line =~ ";" ]]
	then
	    line=$line$(sed "$(( 1 + RANDOM % 22))q;d" obfuscated.txt)
	    echo $line
	fi					    
    fi
    echo $line >> $1
done < "$1.bak"

    
