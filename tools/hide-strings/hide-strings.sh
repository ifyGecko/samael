#!/bin/bash

cat $1 > "$1.tmp"

rm $1

while read -r line; do
    if [[ $line =~ "\"" ]] && [[ ! $line =~ "#include" ]]
    then
	str=$(echo $line | cut -d'"' -f 2)
	bf_str=''
	
	for (( i=0; i<${#str}; i++ )); do
	    char2hex=$(echo "${str:$i:1}" | hexdump -v -e '/1 "%02d\n"' | head -n 1)
	    for (( j=0; j<char2hex; j++ )); do
		bf_str+=' '
	    done
	    bf_str+='\b'
	done

	str='"'$str'"'
	bf_str='hidden_string("'$bf_str'")'
	line=${line/"$str"/$bf_str}
	
    fi
    echo -e "${line}" >> $1
done < "$1.tmp"

rm -f "$1.tmp"
