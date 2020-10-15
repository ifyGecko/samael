#!/bin/bash

if [ ${PWD##*/} == "tests" ]
then
    cd ../
fi

cd ../src

for i in {1..15}
do
    ./build.sh clean
    ./build.sh
    ssdeep src/samael >> /tmp/hashes.txt
done

samael_result=$(./build.sh && ssdeep -s -m /tmp/hashes.txt src/samael)

if [ "$samael_result" != "" ]
then
    echo "[X] SSDEEP Test Failed"
else
    echo "[*] SSDEEP Test Passed"
fi

rm /tmp/hashes.txt
