#include "timer.h"

uint8_t initTimer(uint16_t freq)
{
	if(freq < PIT_MINFREQ)
	{
		return -1;//TODO use errno
	}
	
	uint16_t counter = PIT_FREQ / freq;
	//lets get channel 0 to mode 2, access first low, then high
	PIT_COMMAND(PIT_MODE(2) | PIT_ACCESS_ALL | PIT_CHANNEL(0));
	//writes the low and high bit to channel 0
	PIT_WRITE(0, counter);
	
	registerIntHandler(IRQ0, &generalTimerHandler);
	
	return 0;
}