#include "paging.h"

#if ARCH == 32

//Lets first do the memory manager...
//pageDirEntry	pageDir[1024] PAGE_ALIGNED;
//pageTableEntry	KernelPageTable[1024] PAGE_ALIGNED;

#define stdDirEntry(tableAdress)	P_PRESENT | P_ADDR(tableAdress) | P_RW\
									| P_WRITE_THROUGH | P_PAGE_SIZE
#define stdTableEntry(pageAdress)	P_PRESENT | P_ADDR(pageAdress ) | P_RW\
									| P_WRITE_THROUGH

#define P_ADDR(addr)	addr & 0xFFFFF000
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
#define P_PAGE_SIZE		0x80//this would be either 2 MiB or 4 MiB
//dependend on some bit in some register...
#endif /* PAGE_SIZE == 0x1000 */

#define P_TABLE_OFFS(a)	(0x003FF000 & (a)) >> 12
#define P_DIR_OFFS(a)	(0xFFC00000 & (a)) >> 22

void initPaging()
{/*
	//set 1024 * 4 bytes to zero
	memset(pageDir, 0x1000, 0);*/
}

int8_t mapPage()//uint32_t physicalAddr, uint32_t virtualAddr)
{
	return -NOT_IMPLEMENTED;
	/*if(P_PRESENT & pageDir[P_DIR_OFFS(virtualAddr)])
	{
		//page table exists
		uint32_t pTable = P_ADDR(pageDir[P_DIR_OFFS(virtualAddr)]);
		
		
		return -NOT_IMPLEMENTED;
	}
	else
	{
		return -NOT_IMPLEMENTED;
		//allocate 1024 bytes of memory
		//pageDir[P_DIR_OFFS(virtualAddr)] = stdDirEntry(memaddr);
		//create page table
	}*/
}

#else
#error "[ERROR] Currently there is only 32 bit support!"
#endif /* ARCH == 32 */