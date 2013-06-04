#!/bin/bash

# qemu.sh
#
# Compiles and executes the kernel on the test environment qemu. For this to run
# properly the package 'qemu' has to be installed. Qemu can be interfaced with
# GDB via
#	target remote :1234
#
# Copyright (C) 2013 Lasse Schuirmann. All Rights Reserved.
# Written by Lasse Schuirmann (lasse.schuirmann@gmail.com)
#
# This program is free software: you can redistribute it and/or modify it under
# the terms of the GNU General Public License as published by the Free Software
# Foundation, either version 3 of the License, or (at your option) any later
# version.

if make
then
	echo "Compiled successfully. Starting kernel..."
	qemu-system-i386  -soundhw pcspk  -kernel kernel.img  -gdb tcp::1234 -d int -D qemu.log
else
	echo "Failed compiling! Please check compiler errors."
fi
