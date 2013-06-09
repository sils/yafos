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


echo
echo "Welcome to this Q&D tool." # if this ever works...


echo "Creating working directory."
mkdir ~/cc
cd ~/cc

echo "getting crosstool-ng"
## first get the crosstool-ng toolchain builder
wget http://crosstool-ng.org/download/crosstool-ng/crosstool-ng-1.18.0.tar.bz2
echo "done"
echo "...now extracting source"
##extract source
tar xf crosstool-ng-1.18.0.tar.bz2
echo "done"

cd -

## copy patch
cp ./cc/patch_makefile_recursion.patch ~/cc/crosstool-ng-1.18.0/


## get into the source tree
cd ~/cc/crosstool-ng-1.18.0

## patch
echo "Patch Makefile.in"
patch -p1 < patch_makefile_recursion.patch
echo "configure toolchain"
## configure
./configure --prefix=/tmp/ct-ng/
echo "done"
## compile

echo "... install"

make install

cd -

mkdir -p ~/cc/toolchain 

## copy config file
cp ./cc/CONFIG_YAFOS ~/cc/toolchain/.config

cd ~/cc/toolchain


##build toolchain
echo "building toolchain, this process can take up to 3 houres!!"
/tmp/ct-ng/bin/ct-ng build

echo "cleaning"
#rm -R ~/cc
echo "done"

