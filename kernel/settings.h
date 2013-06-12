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

//Architecture (may be: 32, 64)
#define ARCH		32

//Memory
//let a page be 4 KiB
#define PAGE_SIZE	0x1000

//Debug settings
#define DEBUG		true

//Sound settings
#define IRQ_0_FREQ	80
#define BEEP //if its defined it will beep ;)

#endif /* _SETTINGS_H */
