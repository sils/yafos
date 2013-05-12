#!/bin/bash
make
qemu-system-i386 -kernel kernel.img -gdb tcp::1234