#!/bin/bash

# toolchain.sh
#
# Copyright (C) 2013 Matthias Riegler. All Rights Reserved.
# Written by Matthias Riegler (riegler.matthias2@gmail.com)
# 
# This program is free software. You can redistribute it and/or modify it under
# the terms of the GNU General Public License as published by the Free Software
# Foundation, either version 3 of the License, or (at your option) any later
# version.

if [ "$(id -u)" != "0" ]; then
   echo "To build and install the toolchain, you have to run make as root!"
   exit 1
fi

bash ./cc/install.sh
