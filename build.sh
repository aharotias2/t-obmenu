#!/bin/bash

printf "Password:"
stty -echo
read PASSWORD
stty echo
echo
echo "Your password is $PASSWORD"

