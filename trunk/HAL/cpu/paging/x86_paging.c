/* x86_paging.c
 * 
 * Provides paging code for the x86 processor architecture.
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

//TODO update code guidelines:
//	1. where to put macros
//	2. ifdefs in architecture dependend code files
#ifdef _X86_PAGING_H

#include <string.h>
#include <stdMacro.h>
#include <settings.h>
#include <mem/physical/pMem.h>
#include <cpu/paging/pagedAlloc.h>
#include <intHandlers/generalInt.h>

extern int32_t activatePaging(void *pageDirAddr);

typedef uint32_t	pageDirEntry;
typedef uint32_t	pageTableEntry;

static pageDirEntry *	pageDir;
static bool active;

#define stdEntry(tableAdress)	(P_PRESENT | P_ADDR(tableAdress) | P_RW)

#define P_ADDR(addr)	(addr & 0xFFFFF000)
//flags
#define P_PRESENT		0x01
#define P_RW			0x02
#define P_SUPER			0x04
#define P_WRITE_THROUGH	0x08
#define P_NO_CACHE		0x10
#define P_USED			0x20
#if PAGE_SIZE == 0x1000
#define P_PAGE_SIZE		0x00
#else
#warning "Using another page size than 4KiB was never tried!"
#define P_PAGE_SIZE		0x80//this would be either 2 MiB or 4 MiB
//dependend on some bit in some register...
#endif /* PAGE_SIZE == 0x1000 */

#define P_TABLE_OFFS(a)	(((a)<<10) >> 22)
#define P_DIR_OFFS(a)	((a) >> 22)

static void pageFaultHandler(registers_t *regs)
{
	uint32_t cr2;
	ASM("mov %%cr2, %0" : "=r" (cr2));
	fatalErr("\nA page fault occurred!\n\
  Adress         : %x\n\
  Faulting Adress: %x\n\
  Error Code     : %x\n", regs->eip, cr2, regs->errCode);
}

extern inline void initPaging()
{
	sti();
	active = false;
	
	pageDir = (pageDirEntry *)pMemAlloc((1024*sizeof(pageDirEntry)+PAGE_SIZE-1)
							/ PAGE_SIZE);
	
	if(pageDir == NULL)
	{
		fatalErr("Failed allocating memory for page directory!");
	}
	
	memset(pageDir, 0, 1024*sizeof(pageDirEntry));
	mapPage((uintptr_t)pageDir, (uintptr_t)pageDir);
	
	//map space for future page tables
	pagedMemInit(PAGED_MEM_SIZE);
	
	registerIntHandler(0xe,&pageFaultHandler);
}

extern inline uint32_t loadPageTable()
{
	//TODO search cr register
	active = true;
	return activatePaging((void *)pageDir);
}

extern inline void setPageDir(void *pDir)
{
	pageDir = pDir;
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

err_t mapPage(uintptr_t physicalAddr, uintptr_t virtualAddr)
{
	pageTableEntry* pTable;
	
	//it's impossible, that the values are out of range
	//so probably no unallocated space will be overwritten
	
	if(P_PRESENT & pageDir[P_DIR_OFFS(virtualAddr)])
	{
		pTable = (pageTableEntry *)P_ADDR(pageDir[P_DIR_OFFS(virtualAddr)]);
		if(P_PRESENT & pTable[P_TABLE_OFFS(virtualAddr)])
		{
			return -OBJECT_PRESENT;
		}
		pTable[P_TABLE_OFFS(virtualAddr)] = stdEntry(physicalAddr);
		return SUCCESS;
	}
	//create empty page table, 1024 entries;
	if(active)
	{
		pTable =(pageTableEntry *)pagedMemAlloc((1024*sizeof(pageTableEntry)
												+PAGE_SIZE - 1)/PAGE_SIZE);
	}
	else
	{
		pTable =(pageTableEntry *)pMemAlloc((1024*sizeof(pageTableEntry)
											+PAGE_SIZE - 1)/PAGE_SIZE);
	}
	if(pTable == NULL)
	{
		fatalErr("Memory allocation failed.");
	}
	memset(pTable, 0, 1024*sizeof(pageTableEntry));
	
	pageDir[P_DIR_OFFS(virtualAddr)] = stdEntry((uintptr_t)pTable);
	pTable[P_TABLE_OFFS(virtualAddr)] = stdEntry(physicalAddr);
	
	if(!active)
	{
		assertSuccess(mapRegion((uintptr_t)pTable, (uintptr_t)pTable,
						(uintptr_t)pTable + 1024*sizeof(pageTableEntry)));
	}
	
	return SUCCESS;
}

#endif /* _X86_PAGING_H */