# Makefile
#
# TODO
#
# Copyright (C) 2013 Lasse Schuirmann. All Rights Reserved.
# Written by Lasse Schuirmann (lasse.schuirmann@gmail.com)
# 
# This program is free software. You can redistribute it and/or modify it under
# the terms of the GNU General Public License as published by the Free Software
# Foundation, either version 3 of the License, or (at your option) any later
# version.

# No include directories for now.
INCDIRS	=
# Don't let the C compiler do anything from itself
EXCLUDE	= -nostdlib -nostdinc -fno-builtin -nostartfiles -nodefaultlibs\
-ffreestanding
# No optimization
OPT	= -O0
# All and extra warnings
WARNLEV	= -Wall -Wextra -std=c99 -pedantic
# Compile with debug symbols (e.g. for gdb)
DEBUG	= -g
CFLAGS	= $(ARCH) $(WARNLEV) $(EXCLUDE) $(INCDIRS) $(DEBUG) $(OPT)


CC32	= ~/yafoscc/i386-yafos-elf/bin/i386-yafos-elf-gcc
CC64	= ~/yafoscc/x86_64-yafos-elf/bin/x86_64-yafos-elf-gcc
CCARM   = ~/yafoscc/arm-yafos-elf/bin/arm-yafos-elf-gcc

AS32	= ~/yafoscc/i386-yafos-elf/bin/i386-yafos-elf-as
AS64	= ~/yafoscc/x86_64-yafos-elf/bin/x86_64-yafos-elf-as
ASARM   = ~/yafoscc/arm-yafos-elf/bin/arm-yafos-elf-as

LD32	= ~/yafoscc/i386-yafos-elf/bin/i386-yafos-elf-ld
LD64	= ~/yafoscc/x86_64-yafos-elf/bin/x86_64-yafos-elf-ld
LDARM   = ~/yafoscc/arm-yafos-elf/bin/arm-yafos-elf-ld

# Linker script
LDFLAGS	= -T linker.ld

SRCS	= $(shell find ./ -name '*.c')
OBJFILES= $(addsuffix .o,$(basename $(SRCS)))

testmodule.bin: $(OBJFILES)
	$(LD32) $(LDFLAGS) -o $@ $^

.c.o:
	$(CC32) $(CFLAGS) -o $@ -c $<

clean:
	$(RM) $(OBJFILES) testmodule.bin