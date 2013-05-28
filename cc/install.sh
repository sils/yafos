#!/bin/bash

echo "/-------------------------------------------\\"
echo "|                                           |"
echo "|                 YAFOS CCI                 |"
echo "|     (Installer for the cross compiler)    |"
echo "|        (c) 2013 by Lasse Schuirmann       |"
echo "|                                           |"
echo "\\-------------------------------------------/"

if [ "$(id -u)" != "0" ]; then
   echo "This script must be run as root!"
   exit 1
fi

echo
echo "Welcome to this Q&D tool." # if this ever works...
echo "It will create a directory 'cc' in your home directory for all temporary files."
echo "Where do you want the cross compiler to be? (exact path please! e.g. /home/user/cross or global /usr/local/cross)"
read cpath
mkdir $cpath
ctarget=i586-elf

echo
echo "Creating working directory."
mkdir ~/cc
cd ~/cc
wget ftp://ftp.gnu.org/gnu/gcc/gcc-4.8.0/gcc-4.8.0.tar.bz2
tar -xjf gcc-4.8.0.tar.bz2 &
gccpid=$!

wget ftp://ftp.gnu.org/gnu/binutils/binutils-2.23.2.tar.bz2
tar -xjf binutils-2.23.2.tar.bz2 &
binupid=$!

wget ftp://ftp.gmplib.org/pub/gmp-5.1.2/gmp-5.1.2.tar.bz2
tar -xjf gmp-5.1.2.tar.bz2

wget http://multiprecision.org/mpc/download/mpc-1.0.1.tar.gz
tar -xf mpc-1.0.1.tar.gz

wget http://www.mpfr.org/mpfr-current/mpfr-3.1.2.tar.bz2
tar -xjf mpfr-3.1.2.tar.bz2

echo "Moving sources."
mv gmp-5.1.2 gcc-4.8.0/gmp
mv mpfr-3.1.2 gcc-4.8.0/mpfr
mv mpc-1.0.1 gcc-4.8.0/mpc

mkdir buildgcc
mkdir buildbinutils

cd buildgcc
echo "Check if binutils is unpacked. If not wait."
wait $binupid
# TODO
#../binutils-2.23.2/configure --target=$ctarget --prefix=$PREFIX --disable-nls
#make
#make install

cd ..

cd buildgcc
wait $gccpid
