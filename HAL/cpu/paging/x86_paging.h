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

#ifndef _X86_PAGING_H
#define _X86_PAGING_H

#include <settings.h>
#include <stdint.h>

typedef uint32_t	pageDirEntry;
typedef uint32_t	pageTableEntry;

void initPaging();
int8_t mapPage(uintptr_t physicalAddr, uintptr_t virtualAddr);

//TODO returns cr0 - check it
extern int32_t activatePaging(void *pageDirAddr);

#include <string.h>
#include <errno.h>
#include <stdMacro.h>
#include <mem/physical/pMem.h>

#endif /* _X86_PAGING_H */
