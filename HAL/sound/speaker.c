#include "speaker.h"

//TODO macros :)
void beepOn(uint32_t frequency)
{
	uint8_t tmp;
	initSpeakerTimer(frequency);
	
	//TODO what happens here?
	tmp = inb(0x61);
	if (tmp != (tmp | 3))
	{
		outb(0x61, tmp | 3);
 	}
}

void beepOff()
{
	//TODO what happens here
	uint8_t tmp = (inb(0x61) & 0xFC);
	outb(0x61, tmp);
}