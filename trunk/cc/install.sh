#!/bin/bash

# install.sh
#
# Copyright (C) 2013 Matthias Riegler. All Rights Reserved.
# Written by Matthias Riegler (riegler.matthias2@gmail.com)
# 
# This program is free software. You can redistribute it and/or modify it under
# the terms of the GNU General Public License as published by the Free Software
# Foundation, either version 3 of the License, or (at your option) any later
# version.

echo "/-------------------------------------------\\"
echo "|                                           |"
echo "|                 YAFOS CCI                 |"
echo "|     (Installer for the cross compiler)    |"
echo "|        (c) 2013 by Matthias Riegler       |"
echo "|                                           |"
echo "\\-------------------------------------------/"

if [ "$(id -u)" != "0" ]; then
   echo "This script must be run as root!"
   exit 1
fi

echo
echo "Welcome to this Q&D tool." # if this ever works...


echo "Creating working directory."
mkdir ~/cc
cd ~/cc

echo "getting crosstool-ng"
## first get the crosstool-ng toolchain builder
wget http://crosstool-ng.org/download/crosstool-ng/crosstool-ng-1.15.3.tar.bz2
echo "done"
echo "...now extracting source"
##extract source
tar xf crosstool-ng-1.15.3.tar.bz2
echo "done"

cd -

## get into the source tree
cd ~/cc/crosstool-ng-1.15.3
echo "configure toolchain"
##configure
./configure --prefix=/opt/cross-ng/
echo "done"
## compile

echo "... install"

make install

cd -

mkdir -p ~/cc/toolchain 

## copy config file
cp CONFIG_YAFOS ~/cc/toolchain/.config

cd ~/cc/toolchain


##build toolchain
echo "building toolchain, this process can take up to 3 houres!!"
/opt/cross-ng/bin/ct-ng build




