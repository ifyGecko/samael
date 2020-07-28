#!/bin/bash

if [ ! -f "$1.bak" ]
then
    cat $1 > "$1.bak"
fi

rm $1

header=$(find / -name hide-strings.h 2> /dev/null)

header='#include "'$header'"'

echo $header > $1

while read line; do
    if [[ $line =~ "\"" ]] && [[ ! $line =~ "#include" ]]
    then
	str=$(echo $line | cut -d'"' -f 2)
	bf_str=''
	
	for (( i=0; i<${#str}; i++ )); do
	    dec=$(echo "${str:$i:1}" | hexdump -v -e '/1 "%02d\n"' | head -n 1)
	    for (( j=0; j<dec; j++ )); do
		bf_str+='+'
	    done
	    bf_str+='>'
	done

	str='"'$str'"'
	bf_str='bf_eval("'$bf_str'")'
	line=${line/$str/$bf_str}

    fi
    echo -e "${line}" >> $1
done < "$1.bak"
