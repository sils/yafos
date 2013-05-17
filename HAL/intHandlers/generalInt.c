#include "generalInt.h"

void generalIntHandler(registers_t *regs)
{
	kprintf("Unhandled interrupt (%d)\nHalting kernel.\n", regs->int_no);
	regDump(*regs);
	hltLoop();
}