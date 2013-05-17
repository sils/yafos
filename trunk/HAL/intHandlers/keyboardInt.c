#include "keyboardInt.h"

void generalKbdHandler(registers_t *regs)
{
	kprintf("Unhandled kbd interrupt (%d)\nHalting kernel.\n", regs->intNo);
	kprintf("TODO - Kbd handler\n");
	return;
}