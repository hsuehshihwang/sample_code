#!/bin/bash
cmd(){
	cmd_magic="\x11\x22\x33\x44"
	cmd_type=$(printf "%08x" $1 | sed "s/\(..\)/\\\\x\1/g")
	cmd_len=$(printf "%08x" $2 | sed "s/\(..\)/\\\\x\1/g")
	echo -ne "$cmd_magic$cmd_type$cmd_len$3"
}
cmd 1 5 12345
echo 
echo -ne "$(echo -ne "\x11\x22\x33\x44")"
exit 0; 
(type=1; len=5; echo -ne "\x11\x22\x33\x44$(printf "%08x" $type | sed "s/\(..\)/\\\\x\1/g")$(printf "%08x" $len | sed "s/\(..\)/\\\\x\1/g")\x31\x32\x33\x34\x35") | nc localhost 54188
