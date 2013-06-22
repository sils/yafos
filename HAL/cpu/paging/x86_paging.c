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
#include <mem/physical/pMem.h>

extern int32_t activatePaging(void *pageDirAddr);

typedef uint32_t	pageDirEntry;
typedef uint32_t	pageTableEntry;

pageDirEntry *	pageDir;

#define stdDirEntry(tableAdress)	(P_PRESENT | P_ADDR(tableAdress) | P_RW)
#define stdTableEntry(pageAdress)	(P_PRESENT | P_ADDR(pageAdress ) | P_RW)

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

extern inline void initPaging()
{
	//set 1024 * 4 bytes to zero
	pageDir = (pageDirEntry *)pMemAlloc((1024*sizeof(pageDirEntry))/PAGE_SIZE);
	memset(pageDir, 0, 1024*sizeof(pageDirEntry));
}

extern inline uint32_t loadPageTable()
{
	return activatePaging((void *)pageDir);
}

err_t mapPage(uintptr_t physicalAddr, uintptr_t virtualAddr)
{
	pageTableEntry* pTable;
	
	if(P_PRESENT & pageDir[P_DIR_OFFS(virtualAddr)])
	{
		pTable = (pageTableEntry *)P_ADDR(pageDir[P_DIR_OFFS(virtualAddr)]);
		if(P_PRESENT & pTable[P_TABLE_OFFS(virtualAddr)])
		{
			return -OBJECT_PRESENT;
		}
		else
		{
			pTable[P_TABLE_OFFS(virtualAddr)] = stdTableEntry(physicalAddr);
			return SUCCESS;
		}
	}
	else
	{
		//create empty page table, 1024 entries;
		pTable =(pageTableEntry *)pMemAlloc((1024*sizeof(pageTableEntry))/PAGE_SIZE);
		memset(pTable, 0, 1024*sizeof(pageTableEntry));
		
		pageDir[P_DIR_OFFS(virtualAddr)] = stdDirEntry((uintptr_t)pTable);
		pTable[P_TABLE_OFFS(virtualAddr)] = stdTableEntry(physicalAddr);
		
		return SUCCESS;
	}
}

#endif /* _X86_PAGING_H */