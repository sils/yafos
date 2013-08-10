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

typedef uint64_t PT_entry;

static bool active;
static PT_entry * PML4;

extern int64_t activatePaging(void *pageDirAddr);

//flags
#define P_PRESENT		0x01
#define P_RW			0x02
#define P_SUPER			0x04
#define P_NO_CACHE		0x10
#define P_USED			0x20
#define P_ADDR(addr)	(addr & 0x000FFFFFFFFFF000)

#define stdEntry(tableAdress)	(P_PRESENT | P_ADDR(tableAdress) | P_RW)

#define PML4_OFFS(addr)	((addr >> 39) & 0x1FF)
#define PDPT_OFFS(addr)	(PML4_OFFS(addr << 9))
#define PDT_OFFS(addr)	(PML4_OFFS(addr << 18))
#define PT_OFFS(addr)	(PML4_OFFS(addr << 27))

void * createTable()
{
	PT_entry * tmp;
	//create empty page table, 512 entries;
	if(active)
	{
		tmp =(PT_entry *)pagedMemAlloc((512*sizeof(PT_entry)
										+PAGE_SIZE - 1)/PAGE_SIZE);
	}
	else
	{
		tmp =(PT_entry *)pMemAlloc((512*sizeof(PT_entry)
									+PAGE_SIZE - 1)/PAGE_SIZE);
	}
	if(tmp == NULL)
	{
		fatalErr("Memory allocation failed.");
	}
	memset(tmp, 0, 512*sizeof(PT_entry));
	return tmp;
}

err_t mapPage(uintptr_t physicalAddr, uintptr_t virtualAddr)
{
	//FIXME one could add a subfunction for creating a subtable
	//would be less code.
	PT_entry *tmp, *last;
	//Page-Map Level 4 Table
	if(P_PRESENT & PML4[PML4_OFFS(virtualAddr)])
	{
		//Page Directory Pointer Table
		last = (PT_entry *)P_ADDR((uintptr_t)PML4[PML4_OFFS(virtualAddr)]);
		if(P_PRESENT & last[(uintptr_t)PDPT_OFFS(virtualAddr)])
		{
			//Page Directory Table
			last = (PT_entry *)P_ADDR((uintptr_t)last[PDPT_OFFS(virtualAddr)]);
			if(P_PRESENT & last[(uintptr_t)PDT_OFFS(virtualAddr)])
			{
				//Page Table
				last = (PT_entry *)P_ADDR(last[(uintptr_t)PDT_OFFS(virtualAddr)]);
				if(P_PRESENT & last[(uintptr_t)PT_OFFS(virtualAddr)])
				{
					return -OBJECT_PRESENT;
				}
				last[PT_OFFS(virtualAddr)] = stdEntry(physicalAddr);
				return SUCCESS;
			}
			tmp = createTable();
			last[PDT_OFFS(virtualAddr)] = stdEntry((uintptr_t)tmp);
			if(!active)
			{
				assertSuccess(mapRegion((uintptr_t)tmp, (uintptr_t)tmp,
								(uintptr_t)tmp + 512*sizeof(PT_entry)));
			}
			tmp[PT_OFFS(virtualAddr)] = stdEntry(physicalAddr);
			return SUCCESS;
		}
		//create PDT
		tmp = createTable();
		last[PDPT_OFFS(virtualAddr)] = stdEntry((uintptr_t)tmp);
		if(!active)
		{
			assertSuccess(mapRegion((uintptr_t)tmp, (uintptr_t)tmp,
							(uintptr_t)tmp + 512*sizeof(PT_entry)));
		}
		
		//switch to the new PDT
		last = (PT_entry *)P_ADDR(last[PDPT_OFFS(virtualAddr)]);
		//create PT
		tmp = createTable();
		last[PDT_OFFS(virtualAddr)] = stdEntry((uintptr_t)tmp);
		if(!active)
		{
			assertSuccess(mapRegion((uintptr_t)tmp, (uintptr_t)tmp,
							(uintptr_t)tmp + 512*sizeof(PT_entry)));
		}
		
		//and the entry
		tmp[PT_OFFS(virtualAddr)] = stdEntry(physicalAddr);
		return SUCCESS;
	}
	//create PDPT
	tmp = createTable();
	PML4[PML4_OFFS(virtualAddr)] = stdEntry((uintptr_t)tmp);
	if(!active)
	{
		assertSuccess(mapRegion((uintptr_t)tmp, (uintptr_t)tmp,
						 (uintptr_t)tmp + 512*sizeof(PT_entry)));
	}
	
	//switch to the new PDPT
	last = (PT_entry *)P_ADDR(last[PML4_OFFS(virtualAddr)]);
	//create PDT
	tmp = createTable();
	last[PDPT_OFFS(virtualAddr)] = stdEntry((uintptr_t)tmp);
	if(!active)
	{
		assertSuccess(mapRegion((uintptr_t)tmp, (uintptr_t)tmp,
						 (uintptr_t)tmp + 512*sizeof(PT_entry)));
	}
	
	//switch to the new PDT
	last = (PT_entry *)P_ADDR(last[PDPT_OFFS(virtualAddr)]);
	//create PT
	tmp = createTable();
	last[PDT_OFFS(virtualAddr)] = stdEntry((uintptr_t)tmp);
	if(!active)
	{
		assertSuccess(mapRegion((uintptr_t)tmp, (uintptr_t)tmp,
						 (uintptr_t)tmp + 512*sizeof(PT_entry)));
	}
	
	//and the entry
	tmp[PT_OFFS(virtualAddr)] = stdEntry(physicalAddr);
	return SUCCESS;
}

extern inline void initPaging()
{
	sti();
	active = false;
	
	PML4 = (PT_entry *)pMemAlloc((512*sizeof(PT_entry)+PAGE_SIZE-1)
							/ PAGE_SIZE);
	
	if(PML4 == NULL)
	{
		fatalErr("Failed allocating memory for page-map level 4 table!");
	}
	
	memset(PML4, 0, 512*sizeof(PT_entry));
	mapPage((uintptr_t)PML4, (uintptr_t)PML4);
	
	//map space for future page tables
	pagedMemInit(PAGED_MEM_SIZE);
}

extern inline void setPageDir(void *pDir)
{
	PML4 = pDir;
}

extern inline uint32_t loadPageTable()
{
	//TODO search cr register
	active = true;
	return activatePaging((void *)PML4);
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

#endif /* _X64_PAGING_H */