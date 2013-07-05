#include "pMem.h"

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
void pMemInit(const mMap_t * mMapAddr, const uint32_t mMapLen)
#else
void pMemInit()
#endif
{
	char * tmp;
	
	tmp =  (char *)bitmap + (uint32_t)KERNEL_END/(8*PAGE_SIZE);//size in BYTES!
	
	memset(tmp,				0xFF, 4*BITMAP_SIZE - (uint32_t)KERNEL_END/(8*PAGE_SIZE));
	memset((char *)bitmap,	0x00, (uint32_t)KERNEL_END/(8*PAGE_SIZE));
	#ifdef USE_GRUB_MAP
	#error "NOT FULLY IMPLEMENTED YET!"
	//TODO don't start at one MB if USE_GRUB_MAP
	//use space within the first MB to store the bitmap -> let the bitmap begin
	//	at 1MB
	//TODO determine memory size... :(
	mMap_t * tmp = mMapAddr + mMapLen;
	while(mMapAddr < tmp)
	{
		if(mMapAddr->type == 1)
		{
			//TODO this address is available IF the kernel does not lie here
		}
		 mMapAddr++;
	}
	#endif /* USE_GRUB_MAP */
	
	lastFreeIndex = (uint32_t)KERNEL_END/PAGE_SIZE;
}

void pMemFreeAdv(const uintptr_t addr, uint32_t count)
{
	uintptr_t tmp = addr/PAGE_SIZE;
	
	lastFreeIndex = tmp;
	for(; count > 0; count--)
	{
		SETBIT(bitmap[tmp/32], tmp % 32);
		tmp++;
	}
}

static void pMemSet(const uintptr_t start, uint32_t count)
{
	uintptr_t tmp = start/PAGE_SIZE;
	for(; count > 0; count--)
	{
		CLEARBIT(bitmap[tmp/32], tmp % 32);
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
			if(bitmap[lastFreeIndex/32] & (1<<(lastFreeIndex % 32)))
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
				return (void*)tmp;
			}
			
			lastFreeIndex++;
			if(lastFreeIndex >= BITMAP_SIZE)
			{
				tmpcount = 0;
				lastFreeIndex = (uint32_t)KERNEL_END/PAGE_SIZE;
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