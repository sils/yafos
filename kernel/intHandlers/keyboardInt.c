#include "keyboardInt.h"

void generalKbdHandler(registers_t *regs)
{
	printErr("Unhandled keyboard interrupt (%d) TODO", regs->intNo);
	//remove scancode
	inb(0x60);
	return;
}