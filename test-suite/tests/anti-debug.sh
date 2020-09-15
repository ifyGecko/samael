#!/bin/bash

if [ ${PWD##*/} == "tests" ]
then
    cd ../
fi

cd ../src
./build.sh clean > /dev/null
./build.sh > /dev/null
r2 -c 'db entry0;dc;dc;dc;q!!!' -d samael 2> /dev/null
x=$(ls | grep -Fx samael) > /dev/null
if [ "$x" == 'samael' ]
then
    echo "[*] Anti-debug Test Passed"
else
    echo "[X] Anti-debug Test Failed"
fi
