/* init.c
 * 
 * Defines some constants for easily adjust settings
 *
 * Copyright (C) 2013 Lasse Schuirmann. All Rights Reserved.
 * Written by Lasse Schuirmann (lasse.schuirmann@gmail.com)
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 */

#ifndef _SETTINGS_H
#define _SETTINGS_H

//Architecture
#ifdef __i386__
#define ARCH		32
#elif __x86_64__
#define ARCH		64
#else
#error "Unsupported architecture!"
#endif

//Memory
//let a page be 4 KiB
#define PAGE_SIZE	(0x400)
//wether to use available space from below 1MB
//#define USE_GRUB_MAP

//Debug settings
#define DEBUG

//Sound settings
#define IRQ_0_FREQ	80

#endif /* _SETTINGS_H */
