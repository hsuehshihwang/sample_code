#!/bin/bash
output_target=elf64-x86-64
# arch=x86-64
arch=i386:x86-64
original_binary=sample
output_object=binary.o
objcopy -v --input-target binary \
	--output-target $output_target \
	--binary-architecture $arch \
	$original_binary $output_object


exit 0; 

objcopy --input-target binary \
	--output-target $output_target \
	--binary-architecture $arch \
	$original_binary $output_object
