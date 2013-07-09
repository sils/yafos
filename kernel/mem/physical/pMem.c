#include "pMem.h"

#include <mem/generalMem.h>

static uint32_t bitmap[BITMAP_SIZE];
static genmem_t obj;

void pMemInit()
{
	obj.bitmap = bitmap;
	obj.bitmapSize = BITMAP_SIZE;
	genMemInit(&obj);
	
	//reserve everything up to the physical kernel end
	memset((char *)bitmap,	0x00, (uint32_t)(KERNEL_END + (8*PAGE_SIZE) - 1)/(8*PAGE_SIZE));
}

extern inline void pMemFreeAdv(const uintptr_t addr, uint32_t count)
{
	genMemFreeAdv(&obj, addr, count);
}

extern inline void * pMemAlloc(const uint32_t count)
{
	void *ret = genMemAlloc(&obj, count);
	return ret;
}