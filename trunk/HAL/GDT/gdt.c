#include "gdt.h"

#define ACCESSED_BIT	1<<0
#define RW_BIT			1<<1
#define EXP_DIR_BIT		1<<2//TODO WHAT THE HELL DOES THIS BIT???
/*  DC: Direction bit/Conforming bit.
 * 
 *    Direction bit for data selectors: Tells the direction. 0 the segment grows up. 1 the segment grows down, ie. the offset has to be greater than the base.
 *    Conforming bit for code selectors:
 *        If 1 code in this segment can be executed from an equal or lower privilege level. For example, code in ring 3 can far-jump to conforming code in a ring 2 segment. The privl-bits represent the highest privilege level that is allowed to execute the segment. For example, code in ring 0 cannot far-jump to a conforming code segment with privl==0x2, while code in ring 2 and 3 can. Note that the privilege level remains the same, ie. a far-jump form ring 3 to a privl==2-segment remains in ring 3 after the jump.
 *        If 0 code in this segment can only be executed from the ring set in privl. 
 * 
 */
#define EXEC_BIT		1<<3
#define CODEDATA_BIT	1<<4//if unset this is for other use than code or data
#define DPL_BITS(dpl)	(dpl)<<5 //bits 5 and 6
#define VIRTUAL_BIT		1<<7

#define LIMIT_BITS(a)	((a) & 0xF0000)>>8 //(a<<16)>>8, 4 bits
#define AVAIL_BIT		1<<12
#define LONG_BIT		1<<13 //only for 64 bit mode!!!
#define _32_BIT			1<<14
#define GRAN_BIT		1<<15

static gdtEntry gdtSetGate(uint32_t baseAddr, uint32_t limit, uint16_t flags)
{
	gdtEntry result;
	
	result.baseLow	= 0xFFFF & baseAddr;
	result.baseMid	= (baseAddr >> 16) & 0xFF;
	result.baseHigh	= (baseAddr >> 24) & 0xFF;
	
	result.limitLow	= 0xFFFF & limit;
	
	result.flags	= flags | LIMIT_BITS(limit);
	
	return result;
}

void installGdt(void)
{
	globalGdtPtr.limit = (sizeof(gdtEntry)*GDT_ENTRIES)-1;
	globalGdtPtr.base  = globalGdt;
	
	//update this if you change the number of entries!
	#if GDT_ENTRIES != 3
		#error "Update the GDT entry counter!"
	#endif
	
	globalGdt[0] = SET_ZERO_GATE();
	globalGdt[1] = SET_CODE_GATE(0, 0xFFFFFFFF);
	globalGdt[2] = SET_DATA_GATE(0, 0xFFFFFFFF);
	
	//flush
	loadGdt();
}