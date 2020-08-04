#!/bin/bash

if [ ! -f "$1.bak" ]
then
    cat $1 > "$1.bak"
fi

rm $1

lineNum="$(grep -n "{" "$1.bak" | head -n 1 | cut -d: -f1)"

while read -r line; do
    if [[  $lineNum == '' ]]
    then
	if [[ $line =~ "optimize(opt)" ]]
	then
	    rand=$((0 + RANDOM % 6))
	    if [ $rand == 4 ]
	    then
		rand="'s'"
	    fi
	    if [ $rand == 5 ]
	    then
		rand="'g'"
	    fi
	    line=${line/(opt)/"($rand)"}
	fi
    else
	if [[ $line =~ "{" ]] || [[ $line =~ ";" ]]
	then
	    rand=$(( 1 + RANDOM % 22))
	    line=$line$(sed "${rand}q;d" ../tools/obfuscator/obfuscator.txt)
	fi
    fi
    echo "$line" >> $1
done < "$1.bak"
