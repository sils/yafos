#include "gdt.h"

static void gdtSetGate(uint8_t index, uint32_t baseAddr, uint32_t limit, uint8_t access, uint8_t gran)
{
	gdt[index].baseLow	= 0xFFFF & baseAddr;
	gdt[index].baseMid	= (baseAddr >> 16) & 0xFF;
	gdt[index].baseHigh	= (baseAddr >> 24) & 0xFF;
	
	gdt[index].limitLow	= 0xFFFF & limit;
	
	gdt[index].access	= access;
	gdt[index].granularity = gran | G_LIMIT(limit);
}

void installGdt(void)
{
	tgdtPtr.limit = (sizeof(gdtEntry)*GDT_ENTRIES)-1;
	tgdtPtr.base  = &gdt;
	
	//update this if you change the number of entries!
	#if GDT_ENTRIES != 3
		#error "Update the GDT entry counter!"
	#endif
	
	//remember to edit the gdtFlush function when editing the gates
	SET_ZERO_GATE(0);
	SET_CODE_GATE(1, 0, 0xFFFFFFFF, 0);
	SET_DATA_GATE(2, 0, 0xFFFFFFFF, 0);
	
	//flush! :)
	cli();
	gdtFlush();
}
