# Standard include directories
INCDIRS	= -I ./include/ -I ./HAL/
# Don't let the C compiler do anything from itself
EXCLUDE	= -nostdlib -nostdinc -fno-builtin -nostartfiles -nodefaultlibs\
-ffreestanding -fno-stack-protector
# All and extra warnings
WARNLEV	= -Wall -Wextra -std=c99 -pedantic
# Crosscompile 32 bit kernel
ARCH	= -m32
# Compile with debug symbols (e.g. for gdb) and without optimization
# DEBUG	= -g -O0

CC	= gcc
CFLAGS	= $(ARCH) $(WARNLEV) $(EXCLUDE) $(INCDIRS) $(DEBUG)
LD	= ld
# 32 bit plus specify linker script
LDFLAGS	= -melf_i386 -T linker.ld

SRCS	= $(shell find -name '*.[csS]')
OBJFILES= $(addsuffix .o,$(basename $(SRCS)))

default: kernel.img

all: clean kernel.img

.s.o:
	nasm -f elf -o $@ $<

.c.o:
	$(CC) $(CFLAGS) -o $@ -c $<

kernel.img: $(OBJFILES)
	$(LD) $(LDFLAGS) -o $@ $^
# maybe it does some difference if loader.o is linked first

#TODO maybe automatically build an iso
#TODO do some research over the phony expression

clean:
	$(RM) $(OBJFILES) kernel.img