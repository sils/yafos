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


abort()
{
	echo "Toolchain builder was interrupted. If you want to continue the build please do it manually."
	cleanup
}

cleanup()
{
	echo "Cleaning working directory."
	rm -f -R $wdir
}

echo "/-------------------------------------------\\"
echo "|                                           |"
echo "|                 YAFOS CCI                 |"
echo "|     (Installer for the cross compiler)    |"
echo "|        (c) 2013 by Matthias Riegler       |"
echo "|                                           |"
echo "\\-------------------------------------------/"

echo
echo "Welcome to the YAFOS Toolchain installer."

if [ "$(id -u)" == "0" ]
then
	echo "WARNING: This script is not intended to run as root!\
Press any key to continue or CTRL + C to abort.
Consider running this script with a developement user."
	read
fi

until ping -W 5 -c 1 google.com >>/dev/null;
do
	echo "No internet connection present! You'll be given the output of 'ip link'."
	echo "If you have an ethernet connection you may execute dhcpcd <thedevice>."
	echo "If you are to establish a wireless connection try running wifi-menu."
	echo "An easy alternative would be your GUI."
	echo "Type exit to return to this script."
	ip link
	echo -n "Do you want to be put into a bash to set up a connection? [y/n]"
	read answer
	if [ "$answer" != "n" ]
	then
		bash
	else
		exit 1
	fi
done

wdir="$HOME/cc"
while [ -d "$wdir" ]
do
	c="c"
	wdir="$wdir$c"
done

trap abort SIGINT

echo "Creating working directory ($wdir)..."
mkdir $wdir
cd $wdir
echo "Done."

echo "Downloading toolchain builder (crosstool-ng)..."
wget http://crosstool-ng.org/download/crosstool-ng/crosstool-ng-1.18.0.tar.bz2
echo "Done."

echo "Extracting source..."
tar xf crosstool-ng-1.18.0.tar.bz2
echo "Done."

cd -

## copy patch
cp ./cc/patch_makefile_recursion.patch $wdir/crosstool-ng-1.18.0/


## get into the source tree
cd $wdir/crosstool-ng-1.18.0

## patch
echo "Applying recursion patch..."
patch -p1 < patch_makefile_recursion.patch
echo "Done."

if [ -d "/tmp/ct-ng"]
then
	rm -R -f /tmp/ct-ng
fi

echo "Configure crosstool-ng..."
./configure --prefix=/tmp/ct-ng/
echo "Done."

echo "Install crosstool-ng..."
make install -j4
echo "Done."

cd -

mkdir -p $wdir/toolchain 

## copy config file
cp cc/CONFIG_YAFOS $wdir/toolchain/.config

cd $wdir/toolchain


##build toolchain
echo "Building toolchain...""
/tmp/ct-ng/bin/ct-ng build
echo "Done."

echo "Cleaning up..."
cleanup
echo "Done."

echo "Toolchain built successfully! Enjoy the compilation!"
