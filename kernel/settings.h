/* init.c
 * 
 * Defines some constants for easily adjust settings
 *
 * Copyright (C) 2013 Lasse Schuirmann. All Rights Reserved.
 * Written by Lasse Schuirmann (lasse.schuirmann@gmail.com)
 *
 * Info about arch macros: http://sourceforge.net/p/predef/wiki/Architectures/
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 */

#ifndef _SETTINGS_H
#define _SETTINGS_H

#include <stdMacro.h>

//Memory
//let a page be 4 KiB
#define PAGE_SIZE		(4*KB)
//size of prepaged memory which is available without need of paging
#define PAGED_MEM_SIZE	(8*MB)

//Debug settings
#define DEBUG

//Sound settings
#define IRQ_0_FREQ	150

#endif /* _SETTINGS_H */
