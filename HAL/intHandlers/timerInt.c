#include "timerInt.h"

void generalTimerHandler(registers_t *regs)
{
	kprintf("Unhandled timer interrupt (%d)\nHalting kernel.\n", regs->intNo);
	kprintf("TODO - Timer handler\n");
	return;
}