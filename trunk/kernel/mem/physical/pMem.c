#include "pMem.h"

#if ARCH == 32
static uint32_t bitmap[BITMAP_SIZE];

static uint32_t lastFreeIndex;

#ifdef DEBUG
void printFreeMem()
{
	uint32_t tmp = MB/(32*PAGE_SIZE);
	kprintf("FREE MEMORY MAP:\n");
	while(tmp<BITMAP_SIZE)
	{
		if(bitmap[tmp])
		{
			kprintf("Map: %x       Bitmap: %x\n", tmp, bitmap[tmp]);
		}
		tmp++;
	}
	kprintf("Done.\n");
}

void printAllocMem()
{
	uint32_t tmp = MB/(32*PAGE_SIZE);
	kprintf("ALLOC MEMORY MAP:\n");
	while(tmp < (BITMAP_SIZE/32))
	{
		if(bitmap[tmp] != 0xFFFFFFFF)
		{
			kprintf("Map: %x       Bitmap: %x\n", tmp, bitmap[tmp]);
		}
		tmp++;
	}
	kprintf("Done.\n");
}
#endif /* DEBUG */

#ifdef USE_GRUB_MAP
void pMemInit(const mMap * mMapAddr, const uint32_t mMapLen)
#else
void pMemInit()
#endif
{
	char * tmp;
	
	tmp =  (char *)bitmap + MB/(8*PAGE_SIZE);//size in BYTES!
	
	memset((char *)bitmap, 0, MB/(8*PAGE_SIZE));
	memset(tmp, 0xFF, 4*BITMAP_SIZE - MB/(8*PAGE_SIZE));
	
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
	uintptr_t tmp = addr/PAGE_SIZE;
	for(; count > 0; count--)
	{
		bitmap[tmp/32] |= 1<<(tmp % 32);
		tmp++;
	}
	lastFreeIndex = tmp;
}

//TODO use macros for bitset and so on
void pMemSet(const uintptr_t start, uint32_t count)
{
	uintptr_t tmp = start/PAGE_SIZE;
	for(; count > 0; count--)
	{
		bitmap[tmp/32] &= ~(1<<(tmp % 32));
		//kprintf("[SET] Index: %u, bit %u\n[SET] BITMAP IS: %x\n", tmp/32, tmp%32, bitmap[tmp/32]);
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
				pMemSet(tmp=(lastFreeIndex - tmpcount + 1)*PAGE_SIZE, count);
				return (void*)tmp;
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