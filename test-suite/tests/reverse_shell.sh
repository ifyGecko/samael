#!/bin/bash
user=$(whoami) > /dev/null
killall test 2> /dev/null

if [ ${PWD##*/} == "tests" ]
then
    cd ../
fi

cd ../src
make clean > /dev/null
make > /dev/null
./samael > /dev/null
./test > /dev/null
output=$((echo -e 'whoami\nexit' | nc -lvp 1337) 2> /dev/null)
if [ "$output" != "$user" ]
then
    echo "[X] Reverse Shell Test Failed"
else
    echo "[*] Reverse Shell Test Passed"
fi
