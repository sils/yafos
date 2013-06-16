#include "timer.h"

uint8_t initChannel(uint16_t freq, uint8_t channel, uint8_t mode)
{
	if(freq < PIT_MINFREQ)
	{
		kprintf("[ERROR] FREQUENCY IS TOO LOW!\n");
		return -ERANGE;
	}
	
	uint16_t counter = PIT_FREQ / freq;
	//lets get channel 0 to mode 2, access first low, then high
	PIT_COMMAND(PIT_MODE(mode) | PIT_ACCESS_ALL | PIT_CHANNEL(channel));
	//writes the low and high bit to channel 0
	PIT_WRITE(channel, counter);
	
	return 0;
}