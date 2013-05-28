#include "generalInt.h"

void generalIntHandler(registers_t *regs)
{
	kprintf("Unhandled interrupt (%d)\nHalting kernel.\n", regs->intNo);
	//regDump(*regs);//maybe later - for now it's not so nice
	if(regs->intNo > IRQ0)
	{
		endInterrupt(regs->intNo);
	}
	hltLoop();
}