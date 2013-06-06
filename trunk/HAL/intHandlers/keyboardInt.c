#include "keyboardInt.h"

void generalKbdHandler(registers_t *regs)
{
	kprintf("Unhandled keyboard interrupt (%d) TODO\n", regs->intNo);
	//remove scancode
	inb(0x60);
	return;
}