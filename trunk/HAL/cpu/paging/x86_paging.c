#include "paging.h"

//TODO update code guidelines
#ifdef _X86_PAGING_H

pageDirEntry	pageDir[1024] PAGE_ALIGNED;
//pageTableEntry	KernelPageTable[1024] PAGE_ALIGNED;

#define stdDirEntry(tableAdress)	(P_PRESENT | P_ADDR(tableAdress) | P_RW\
									| P_WRITE_THROUGH | P_PAGE_SIZE)
#define stdTableEntry(pageAdress)	(P_PRESENT | P_ADDR(pageAdress ) | P_RW\
									| P_WRITE_THROUGH)

#define P_ADDR(addr)	(addr & 0xFFFFF000)
//flags
#define P_PRESENT		0x01
#define P_RW			0x02
#define P_SUPER			0x04
#define P_WRITE_THROUGH	0x08
#define P_NO_CACHE		0x10
#define P_USED			0x20
#if PAGE_SIZE == 0x400
#define P_PAGE_SIZE		0x00
#else
#define P_PAGE_SIZE		0x80//this would be either 2 MiB or 4 MiB
//dependend on some bit in some register...
#endif /* PAGE_SIZE == 0x1000 */

#define P_TABLE_OFFS(a)	((0x003FF000 & (a)) >> 12)
#define P_DIR_OFFS(a)	((0xFFC00000 & (a)) >> 22)

void initPaging()
{
	//set 1024 * 4 bytes to zero
	memset(pageDir, 0x1000, 0);
}

int8_t mapPage(uintptr_t physicalAddr, uintptr_t virtualAddr)
{
	if(P_PRESENT & pageDir[P_DIR_OFFS(virtualAddr)])
	{
		//page table exists
		//uint32_t pTable = P_ADDR(pageDir[P_DIR_OFFS(virtualAddr)]);
		
		
		return -NOT_IMPLEMENTED;
	}
	else
	{
		kprintf("size: (should be 4): %u\n", (1024*sizeof(pageTableEntry))/PAGE_SIZE);
		//create page table, 1024 entries
		pageDir[P_DIR_OFFS(virtualAddr)]  = stdDirEntry((uintptr_t)pMemAlloc((1024*sizeof(pageTableEntry))/PAGE_SIZE));
		//it's page aligned!
		pageTableEntry* pTable = (pageTableEntry *)P_ADDR(pageDir[P_DIR_OFFS(virtualAddr)]);
		pTable[P_TABLE_OFFS(virtualAddr)] = stdTableEntry(physicalAddr);
		
		return 0;
	}
}

#endif /* _X86_PAGING_H */