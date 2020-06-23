#!/bin/bash
tests/ssdeep.sh $1
tests/anti-debug.sh $1
tests/bind_shell.sh $1
tests/reverse_shell.sh $1
