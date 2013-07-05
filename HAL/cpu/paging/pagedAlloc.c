#include "pagedAlloc.h"

#include <errno.h>
#include <stdlib.h>
#include <mem/physical/pMem.h>
#include <cpu/paging/paging.h>

static uint32_t *pbitmap;
static uint8_t bitmapSize;
static uint8_t lastFreeIndex;
static uintptr_t offset;

//has to be invoked before paging is enabled!
//TODO make a kind of class for this bitmap stuff - way too much overhead!
void pagedMemInit(uint32_t size)
{
	//alloc pages
	offset  = (uintptr_t)pMemAlloc(size/PAGE_SIZE);
	bitmapSize = (size-1+(PAGE_SIZE*32))/(PAGE_SIZE*32);
	pbitmap = (uint32_t*)pMemAlloc(bitmapSize);
	
	//identitymap pages
	assertSuccess(mapRegion(offset, offset, offset + size));
	lastFreeIndex = 0;
}

void pagedMemFree(const uintptr_t addr, uint8_t count)
{
	uintptr_t tmp = (addr-offset)/PAGE_SIZE;
	for(; count > 0; count--)
	{
		SETBIT(pbitmap[tmp/32], tmp % 32);
		tmp++;
	}
	lastFreeIndex = tmp;
}

static void pMemSet(const uintptr_t start, uint32_t count)
{
	uintptr_t tmp = start/PAGE_SIZE;
	for(; count > 0; count--)
	{
		CLEARBIT(pbitmap[tmp/32], tmp % 32);
		tmp++;
	}
	lastFreeIndex = tmp;
}

void * pagedMemAlloc(const uint8_t count)
{
	uint32_t tmp = lastFreeIndex, tmpcount = 0;
	if(count == 0)
	{
		return NULL;
	}
	
	do
	{
		if(pbitmap[lastFreeIndex/32])
		{
			if(pbitmap[lastFreeIndex/32] & (1<<(lastFreeIndex % 32)))
			{
				tmpcount++;
			}
			else
			{
				tmpcount = 0;
			}
			
			if(tmpcount >= count)
			{
				pMemSet(tmp=(lastFreeIndex - tmpcount + 1)*PAGE_SIZE, count);
				return (void*)(tmp+offset);
			}
			
			lastFreeIndex++;
			if(lastFreeIndex >= bitmapSize)
			{
				tmpcount = 0;
				lastFreeIndex = 0;
			}
		}
		else
		{
			//big step
			lastFreeIndex = ((lastFreeIndex/32)+1)*32;
			tmpcount = 0;
		}
	}
	while(lastFreeIndex != tmp);
	
	return NULL;
}