#!/bin/bash

if [ -z $1 ]
then
    echo "error: shared object parameter missing"
else
     file_size=$(stat --printf="%s" $1)
     cat <(echo $(printf "%012d" $file_size)) <(cat $1) - | nc 127.0.0.1 1337
fi

