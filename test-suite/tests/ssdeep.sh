#!/bin/bash

if [ ${PWD##*/} == "tests" ]
then
    cd ../
fi

cd ../

for i in {1..15}
do
    make clean > /dev/null; make obfuscated > /dev/null
    ssdeep src/samael > /tmp/samael_hashes.txt
    ssdeep payloads/reverse_shell.so > /tmp/reverse_shell_hashes.txt
    ssdeep payloads/bind_shell.so > /tmp/bind_shell_hashes.txt
done

samael_result=$(make obfuscated > /dev/null && ssdeep -m /tmp/samael_hashes.txt src/samael)
reverse_shell__result=$(make obfuscated > /dev/null && ssdeep -m /tmp/bind_shell_hashes.txt payloads/bind_shell.so)
bind_shell__result=$(make obfuscated > /dev/null && ssdeep -m /tmp/reverse_shell_hashes.txt payloads/reverse_shell.so)

if [ "$samael_result" != "" ] || [ "$reverse_shell_result" != "" ] || [ "$bind_shell_result" != "" ]
then
    echo "[X] SSDEEP Test Failed"
else
    echo "[*] SSDEEP Test Passed"
fi

rm /tmp/*_hashes.txt
