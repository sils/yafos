/* HAL/boot/boot.h
 * 
 * Defines nessecary structures for reading information passed by multiboot
 * compliant bootloaders. See
 * 		http://www.gnu.org/software/grub/manual/multiboot/multiboot.pdf
 * for more information.
 *
 * Copyright (C) 2013 Lasse Schuirmann. All Rights Reserved.
 * Written by Lasse Schuirmann (lasse.schuirmann@gmail.com)
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 */

#ifndef _BOOT_H
#define _BOOT_H

#include <stdint.h>

//defined by linker script
extern uint8_t kernelStart;
extern uint8_t kernelEnd;
#define KERNEL_START	&kernelStart
#define KERNEL_END	&kernelEnd

//TODO multiboot structure
//See multiboot.pdf, page 9

#endif /* _BOOT_H */