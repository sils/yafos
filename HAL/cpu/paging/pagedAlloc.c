#include "pagedAlloc.h"

#include <errno.h>
#include <stdlib.h>
#include <mem/physical/pMem.h>
#include <mem/generalMem.h>
#include <cpu/paging/paging.h>

static uintptr_t offset;
static genmem_t obj;

//has to be invoked before paging is enabled!
//TODO make a kind of class for this bitmap stuff - way too much overhead!
void pagedMemInit(uint32_t size)
{
	//alloc pages
	offset  = (uintptr_t)pMemAlloc((size+PAGE_SIZE-1)/PAGE_SIZE);
	obj.bitmapSize = (size-1+(PAGE_SIZE*32))/(PAGE_SIZE*32);
	obj.bitmap = (uint32_t*)pMemAlloc(obj.bitmapSize);
	
	//identitymap pages
	assertSuccess(mapRegion(offset, offset, offset + size));
	genMemInit(&obj);
}

//TODO untested
void pagedMemFree(const uintptr_t addr, uint8_t count)
{
	genMemFreeAdv(&obj, addr, count);
}

void * pagedMemAlloc(const uint8_t count)
{
	return (void*)(offset + (uintptr_t)genMemAlloc(&obj, count));
}