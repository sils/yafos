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

void initPaging();
//TODO int8_t mapPage(uint32_t physicalAddr, uint32_t virtualAddr);

#else
#error "[ERROR] Currently there is only 32 bit support!"
#endif /* ARCH == 32 */

#include <string.h>
#include <errno.h>
#include <stdMacro.h>

#endif /* _PAGING_H */
