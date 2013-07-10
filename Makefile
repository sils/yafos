# Makefile
#
# Provides the following options
#	default:compile all changes files and link
#	all:	remakes the whole project
#	run:	compile all changed files, link and execute qemu
#	clean:	delete all object files and the kernel image
#	toolchain: configure the crosscompiler for this user of this system
#		Missing dependencies for ubuntu: g++, flex, libtool, gperf, bison, ncurses-dev, gawk
#		Missing dependencies for arch: wget, gperf
#
# Copyright (C) 2013 Lasse Schuirmann. All Rights Reserved.
# Copyright (C) 2013 Matthias Riegler. All Rights Reserved.
# Written by Lasse Schuirmann (lasse.schuirmann@gmail.com)
# 
# This program is free software. You can redistribute it and/or modify it under
# the terms of the GNU General Public License as published by the Free Software
# Foundation, either version 3 of the License, or (at your option) any later
# version.

# Standard include directories
INCDIRS	= -I ./include/ -I ./HAL/ -I ./kernel/
# Don't let the C compiler do anything from itself
EXCLUDE	= -nostdlib -nostdinc -fno-builtin -nostartfiles -nodefaultlibs\
-ffreestanding -m32
# No optimization
OPT	= -O0
# All and extra warnings
WARNLEV	= -Wall -Wextra -std=c99 -pedantic
# Compile with debug symbols (e.g. for gdb)
DEBUG	= -g
CFLAGS	= $(ARCH) $(WARNLEV) $(EXCLUDE) $(INCDIRS) $(DEBUG) $(OPT)


CC32	= gcc
CC64	= ~/yafoscc/x86_64-yafos-elf/bin/x86_64-yafos-elf-gcc
CCARM   = ~/yafoscc/arm-yafos-elf/bin/arm-yafos-elf-gcc

AS32	= ~/yafoscc/i386-yafos-elf/bin/i386-yafos-elf-as
AS64	= ~/yafoscc/x86_64-yafos-elf/bin/x86_64-yafos-elf-as
ASARM   = ~/yafoscc/arm-yafos-elf/bin/arm-yafos-elf-as

LD32	= ld
LD64	= ~/yafoscc/x86_64-yafos-elf/bin/x86_64-yafos-elf-ld
LDARM   = ~/yafoscc/arm-yafos-elf/bin/arm-yafos-elf-ld

# Linker script
LDFLAGS	= -T linker.ld -melf_i386

SRCS	= $(shell find kernel/ -name '*.[csS]')
SRCS   += $(shell find include/ -name '*.[csS]')
SRCS   += $(shell find HAL/ -name '*.[csS]')
OBJFILES= $(addsuffix .o,$(basename $(SRCS)))

# EMULATOR SETTINGS
EMUL	=qemu-system-x86_64
EDEBUG	=-gdb tcp::1234 -d int -D ./qemu.log

default: kernel.img

# just to test how parameters can be used - TODO: invoke codechecker script
echo:
	echo $(TEXT)

all: clean kernel.img

run: kernel.img
	$(EMUL)  -soundhw pcspk -kernel $< $(EDEBUG)

cc32:
	bash ./tools/cc32/toolchain.sh
cc64:	
	bash ./tools/cc64/toolchain.sh
ccarm:
	bash ./tools/arm32/toolchain.sh

.s.o:
	nasm -f elf -o $@ $<

.c.o:
	$(CC32) $(CFLAGS) -o $@ -c $<

kernel.img: $(OBJFILES)
	$(LD32) $(LDFLAGS) -o $@ $^

#TODO maybe automatically build an iso

clean:
	$(RM) $(OBJFILES) kernel.img
