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
#include <settings.h>//TODO try to make functions page size independent!
//use PAGE_SIZE macro!
//TODO determine memory size

void	pMemInit(/* TODO parameter multiboot structure */);//TODO
#if ARCH == 32
void *	pMemAlloc(uint32_t count);
#elif ARCH == 64
void *	pMemAlloc(uint64_t count);
#endif

#endif /* _PMEM_H */
