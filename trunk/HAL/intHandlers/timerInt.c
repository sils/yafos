#include "timerInt.h"

#define FREQCOUNT	12
#define CHORDCOUNT	4
static uint32_t freqs[CHORDCOUNT][FREQCOUNT] =
{
{ 200, 250, 301, 400, 500, 600, 800, 600, 500, 400, 301, 250 },
{ 225, 250, 301, 400, 500, 600, 800, 600, 500, 400, 301, 250 },
{ 200, 250, 301, 400, 500, 600, 800, 600, 500, 400, 301, 250 },
{ 200, 250, 301, 400, 500, 600, 200, 600, 500, 400, 301, 250 }
};

void generalTimerHandler(registers_t *regs)
{
	static uint32_t c=0;
	
#ifdef BEEP
	static uint32_t offs=0, chord=0, d=0;
	
	if(((d%=6) == 0) && (chord == 0 || chord % CHORDCOUNT != 0))
	{
		beepOn(freqs[chord][offs]);
		offs++;
		offs %= FREQCOUNT;
		if(offs==0)
		{
			chord++;
			if(chord % CHORDCOUNT == 0)
				beepOff();
		}
	}
	d++;
#endif /* BEEP */
	c++;
	if(regs->intNo != IRQ0)
	{
		kprintf("The timer was called by the wrong interrupt. Something went wrong!");
		kprintf(" Are you a developer? Have a look at intHandlers/timerInt.c.");
	}
	
	if((c % IRQ_0_FREQ) == 0)
	{
		//kprintf("Another second is over.\n");
		c = 0;
	}
}
