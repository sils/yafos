#include "timerInt.h"

void generalTimerHandler(registers_t *regs)
{
	static uint32_t c=0;

	c++;
	if(regs->intNo != IRQ0)
	{
		printErr("Timer called by the wrong interrupt. Something went wrong!\
Are you a developer? Have a look at intHandlers/timerInt.c.");
	}
	
	if((c % IRQ_0_FREQ) == 0)
	{
		c = 0;
	}
}
