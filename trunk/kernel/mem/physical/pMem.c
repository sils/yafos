#include "pMem.h"

#if ARCH == 32
static uint32_t bitmap[BITMAP_SIZE];

static uint32_t lastFreeIndex;

#ifdef USE_GRUB_MAP
void pMemInit(const mMap * mMapAddr, const uint32_t mMapLen)
#else
void pMemInit()
#endif
{
	char * tmp;
	
	tmp =  (char *)bitmap + MB;
	memset((char *)bitmap, MB, 0);
	memset(tmp, 4*BITMAP_SIZE - MB, 1);
	
	#ifdef USE_GRUB_MAP
	#error "NOT FULLY IMPLEMENTED YET!"
	mMap * tmp = mMapAddr + mMapLen;
	while(mMapAddr < tmp)
	{
		if(mMapAddr->type == 1)
		{
			//TODO this address is available IF the kernel does not lie here
		}
		 mMapAddr++;
	}
	#endif /* USE_GRUB_MAP */
	
	lastFreeIndex = MB/PAGE_SIZE;
}

void pMemFreeAdv(const uintptr_t addr, uint32_t count)
{
	uintptr_t tmp   = addr/PAGE_SIZE;
	for(; count > 0; count--)
	{
		bitmap[tmp/32] |= 1<<(tmp % 32);
		tmp++;
	}
	lastFreeIndex = tmp;
}

void * pMemAlloc(const uint32_t count)
{
	uint32_t tmp = lastFreeIndex, tmpcount = 0;
	
	if(count == 0)
	{
		return NULL;
	}
	
	do
	{
		if(bitmap[lastFreeIndex/32])
		{
			if(1<<(lastFreeIndex % 32))
			{
				tmpcount++;
			}
			else
			{
				tmpcount = 0;
			}
			
			if(tmpcount >= count)
			{
				if(tmpcount != count)
				{
					kprintf("MAJOR ERROR! Something wrong in the pMemManager");
					//TODO halt kernel
				}
				return (void*)((lastFreeIndex - tmpcount + 1)*PAGE_SIZE);
			}
			
			lastFreeIndex++;
			if(lastFreeIndex >= BITMAP_SIZE)
			{
				tmpcount = 0;
				lastFreeIndex = MB/PAGE_SIZE;
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

#else
#error "64-bit mode is not supported by physical memory manager YET."
#endif