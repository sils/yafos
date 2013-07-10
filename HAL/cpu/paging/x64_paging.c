/* x64_paging.c
 * 
 * Provides paging code for the x86_64 processor architecture.
 *
 * Copyright (C) 2013 Lasse Schuirmann. All Rights Reserved.
 * Written by Lasse Schuirmann (lasse.schuirmann@gmail.com)
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 */

#include "paging.h"

#ifdef _X64_PAGING_H

#include <string.h>
#include <sys/io.h>
#include <stdMacro.h>
#include <settings.h>
#include <mem/physical/pMem.h>
#include <cpu/paging/pagedAlloc.h>

static bool active;
void * pageDir;

extern int32_t activatePaging(void *pageDirAddr);

extern inline void initPaging()
{
	sti();
	active = false;
	
	//TODO reserve space for page directory for level 4
	//TODO set it to zero
	//memset(??, 0, ??)
	
	//map space for future page tables and so on
	pagedMemInit(PAGED_MEM_SIZE);
}

extern inline void setPageDir(void *pDir)
{
	pageDir = pDir;
}

extern inline uint32_t loadPageTable()
{
	//TODO search cr register
	active = true;
	return activatePaging((void *)pageDir);
}

err_t mapRegion(uintptr_t physicalStart, uintptr_t virtualStart,
				uintptr_t physicalEnd)
{
	uintptr_t addr = (uintptr_t)physicalStart;
	for(; addr < physicalEnd; addr += PAGE_SIZE)
	{
		if(!verify(mapPage(addr,  (addr - physicalStart) + virtualStart)))
		{
			return -ERR_IN_SUBFUNC;
		}
	}
	return SUCCESS;
}

//TODO
//err_t mapPage(uintptr_t physicalAddr, uintptr_t virtualAddr);

#endif /* _X64_PAGING_H */