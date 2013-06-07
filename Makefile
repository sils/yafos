# Makefile
#
# Copyright (C) 2013 Lasse Schuirmann. All Rights Reserved.
# Written by Lasse Schuirmann (lasse.schuirmann@gmail.com)
# 
# This program is free software. You can redistribute it and/or modify it under
# the terms of the GNU General Public License as published by the Free Software
# Foundation, either version 3 of the License, or (at your option) any later
# version.

# Standard include directories
INCDIRS	= -I ./include/ -I ./HAL/
# Don't let the C compiler do anything from itself
EXCLUDE	= -nostdlib -nostdinc -fno-builtin -nostartfiles -nodefaultlibs\
-ffreestanding
# No optimization
OPT	= -O0
# All and extra warnings
WARNLEV	= -Wall -Wextra -std=c99 -pedantic
# Crosscompile 32 bit kernel, use intel syntax for inline assebly
ARCH	= -m32
# Compile with debug symbols (e.g. for gdb) __attribute__((packed))
DEBUG	= -g

CC	= gcc
CFLAGS	= $(ARCH) $(WARNLEV) $(EXCLUDE) $(INCDIRS) $(DEBUG) $(OPT)
LD	= ld
# 32 bit plus specify linker script
LDFLAGS	= -melf_i386 -T linker.ld

SRCS	= $(shell find -name '*.[csS]')
OBJFILES= $(addsuffix .o,$(basename $(SRCS)))

# EMULATOR SETTINGS
EMUL	=qemu-system-i386
EDEBUG	=-gdb tcp::1234

default: kernel.img

all: clean kernel.img

run: kernel.img
	$(EMUL)  -soundhw pcspk  -kernel $< $(EDEBUG)

.s.o:
	nasm -f elf -o $@ $<

.c.o:
	$(CC) $(CFLAGS) -o $@ -c $<

kernel.img: $(OBJFILES)
	$(LD) $(LDFLAGS) -o $@ $^

#TODO maybe automatically build an iso

clean:
	$(RM) $(OBJFILES) kernel.img