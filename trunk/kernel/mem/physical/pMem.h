/* pMem.h
 * 
 * Provides a physical memory manager which provides pages.
 *
 * Copyright (C) 2013 Lasse Schuirmann. All Rights Reserved.
 * Written by Lasse Schuirmann (lasse.schuirmann@gmail.com)
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 */

#ifndef _PMEM_H
#define _PMEM_H

#include <stdint.h>
#include <settings.h>
#include <stdMacro.h>
//TODO determine memory size

#ifdef USE_GRUB_MAP
void	pMemInit(const mMap_t * mMapAddr, const uint32_t mMapLen);
#else
void 	pMemInit();
#endif

void printFreeMem();
void printAllocMem();

//TODO this is hardware dependent and definitely goes to the HAL!
void *	pMemAlloc(uint32_t count);
void	pMemFreeAdv(const uintptr_t addr, uint32_t count);
#define pMemFree(addr)	pMemFreeAdv((addr),1)

//BITMAP_SIZE*32 are exactly enought bits to adress 4GB of PAGES (!)
//TODO make a macro for changing the 4GB
#define BITMAP_SIZE		((GB/PAGE_SIZE) >> 3)

#include <string.h>
#include <print.h>
#include <boot/multiboot.h>

#endif /* _PMEM_H */
