#include "paging.h"

//TODO update code guidelines:
//	1. where to put macros
//	2. ifdefs in architecture dependend code files
#ifdef _X86_PAGING_H

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
#warning "Using anothern page size than 1024 was never tried!"
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

int8_t loadPageTable()
{
	uint32_t cr0 = activatePaging((void *)pageDir);
	//TODO check cr0
	return SUCCESS;
}

int8_t mapPage(uintptr_t physicalAddr, uintptr_t virtualAddr)
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
		//create page table, 1024 entries;
		pageDir[P_DIR_OFFS(virtualAddr)]  = stdDirEntry(
			(uintptr_t)pMemAlloc((1024*sizeof(pageTableEntry))/PAGE_SIZE));
		//it's page aligned!
		pTable = (pageTableEntry *)P_ADDR(pageDir[P_DIR_OFFS(virtualAddr)]);
		pTable[P_TABLE_OFFS(virtualAddr)] = stdTableEntry(physicalAddr);
		
		return SUCCESS;
	}
}

#endif /* _X86_PAGING_H */