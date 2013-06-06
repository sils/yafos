#include "timerInt.h"

//TODO remove this
#define TCOUNT 7
char tmsg[TCOUNT][18] = {
	"Well,",
	"And now",
	"D'you know:",
	"What about this:",
	"Huuuuh -",
	"Bored? Sorry but",
	"Let's say"
};

void generalTimerHandler(registers_t *regs)
{
	static uint8_t c=0;
	static uint8_t t=20;
	c++;
	if(c % 100 == 0)
	{
		kprintf("%s another second is over.\n", tmsg[t%TCOUNT]);
		c = 0;
		t++;
	}
}
