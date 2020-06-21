#!/bin/bash
tests/ssdeep.sh
tests/bind_shell.sh $1
tests/reverse_shell.sh $1
