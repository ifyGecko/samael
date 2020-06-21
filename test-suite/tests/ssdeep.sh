#!/bin/bash

if [ ${PWD##*/} == "tests" ]
then
    cd ../
fi

cd ../

for i in {1..15}
do
    make clean > /dev/null; make obfuscated > /dev/null
    ssdeep src/samael >> /tmp/hashes.txt
done

samael_result=$(make obfuscated > /dev/null && ssdeep -s -m /tmp/hashes.txt src/samael)

if [ "$samael_result" != "" ]
then
    echo "[X] SSDEEP Test Failed"
else
    echo "[*] SSDEEP Test Passed"
fi

rm /tmp/hashes.txt
