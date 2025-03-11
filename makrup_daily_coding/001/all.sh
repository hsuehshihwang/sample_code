#!/bin/bash

# script name
<< EOF
echo ${BASH_SOURCE[0]}
EOF
# arguments
<< EOF
# result of last command
echo $?
# script arguments numbers
echo $#
# pid of last command
echo $!
# script argumens
echo $@
EOF
# translate hexcode to string
<< EOF
printf "%b" $(echo 41534b5943 | sed 's/../\\x&/g')
echo -ne $(echo 41534b5943 | sed 's/../\\x&/g')
echo 41534b5943 | xxd -r -p 
EOF
