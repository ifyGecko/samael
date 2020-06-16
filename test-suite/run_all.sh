#!/usr/bin/env bash
tests/bind_shell.sh $1
sleep 60
tests/reverse_shell.sh $1
