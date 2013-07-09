#include "generalMem.h"

#include <errno.h>
#include <stdlib.h>
#include <mem/physical/pMem.h>
#include <cpu/paging/paging.h>

void genMemInit(genmem_t *obj)
{
	memset(obj->bitmap, 0xFF, 4*(obj->bitmapSize));
	obj->lastFreeIndex = 0;
}

void genMemFreeAdv(genmem_t *obj, const uintptr_t addr, uint32_t count)
{
	uintptr_t tmp = addr/PAGE_SIZE;
	
	obj->lastFreeIndex = tmp;
	for(; count > 0; count--)
	{
		SETBIT((obj->bitmap)[tmp/32], tmp % 32);
		tmp++;
	}
}

static void genMemSet(genmem_t *obj, const uintptr_t start, uint32_t count)
{
	uintptr_t tmp = start/PAGE_SIZE;
	for(; count > 0; count--)
	{
		CLEARBIT((obj->bitmap)[tmp/32], tmp % 32);
		tmp++;
	}
	obj->lastFreeIndex = tmp;
}

//TODO
void * genMemAlloc(genmem_t *obj, const uint32_t count)
{
	uint32_t tmp = (obj->lastFreeIndex), tmpcount = 0;
	uint32_t lfi = tmp;
	
	if(count == 0)
	{
		return NULL;
	}
	
	do
	{
		if((obj->bitmap)[lfi/32])
		{
			if((obj->bitmap)[lfi/32] & (1<<(lfi % 32)))
			{
				tmpcount++;
			}
			else
			{
				tmpcount = 0;
			}
			
			if(tmpcount >= count)
			{
				genMemSet(obj, tmp=(lfi - tmpcount + 1)*PAGE_SIZE, count);
				obj->lastFreeIndex = lfi;
				return (void*)tmp;
			}
			
			lfi++;
			if(lfi >= (obj->bitmapSize))
			{
				tmpcount = 0;
				lfi = 0;
			}
		}
		else
		{
			//big step
			lfi = ((lfi/32)+1)*32;
			tmpcount = 0;
		}
	}
	while(lfi != tmp);
	
	fatalErr("Out of memory!");
	return NULL;
}