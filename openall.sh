#!/bin/bash
#
# openall.sh
#
# Editor independent project file ;)
#
# Copyright (C) 2013 Lasse Schuirmann. All Rights Reserved.
# Written by Lasse Schuirmann (lasse.schuirmann@gmail.com)
# 
# This program is free software. You can redistribute it and/or modify it under
# the terms of the GNU General Public License as published by the Free Software
# Foundation, either version 3 of the License, or (at your option) any later
# version.

echo "Enter your preferred editor:"
read editor

$editor doc/* tools/*/* README Makefile linker.ld openall.sh */*.[ch] */*/*.[chs]  */*/*/*.inc */*/*/*.[ch] & >> /dev/null &> /dev/null