/* paging.h
 * 
 * Provides hardware dependend functions to set up paging. (In 32 bit mode right
 * now.)
 *
 * Copyright (C) 2013 Lasse Schuirmann. All Rights Reserved.
 * Written by Lasse Schuirmann (lasse.schuirmann@gmail.com)
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 */

#ifndef _PAGING_H
#define _PAGING_H

#include <settings.h>
#include <stdint.h>

#if ARCH == 32
typedef uint32_t	pageDirEntry;
typedef uint32_t	pageTableEntry;

#define P_ADDR(addr)	addr & 0xFFFFF000
//flags
#define P_PRESENT		0x01
#define P_RW			0x02
#define P_SUPER			0x04
#define P_WRITE_THROUGH	0x08 //TODO what is write through? See wiki, cache
#define P_NO_CACHE		0x10
#define P_USED			0x20
#if PAGE_SIZE == 0x1000
#define P_PAGE_SIZE		0x80
#else
#define P_PAGE_SIZE		0x00//this would be either 2 MiB or 4 MiB
//dependend on some bit in some register...
#endif
//TODO there is more...

#else
#error "[ERROR] Currently there is only 32 bit support!"
#endif /* ARCH == 32 */

#endif /* _PAGING_H */
