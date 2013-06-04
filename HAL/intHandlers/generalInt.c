#include "generalInt.h"

void generalIntHandler(registers_t *regs)
{
	static int c=0;
	/* shouldn't be nessecary
	if(regs->intNo > IRQ0)
	{
		endInterrupt(regs->intNo);
	}*/
	if(regs->intNo <= 16)
	{
		c++;
		kprintf("Unhandled exception (%x). Message: %s\n",
			regs->intNo, exceptionMessage[regs->intNo]);
		//TODO standardize exception handling, maybe use keyboard driver to ask
			//which information is to be shown? Continue? Halt?
		//if(regs->intNo == 8)
		//	regDump(*regs);//maybe later - for now it's not so nice
		if(c > 3)
		{
			kprintf("Halting kernel.");
			for(;;)
			{
				cli();
				hlt();
			}
		}
	}
	else
		kprintf("Unhandled interrupt (%x)!\n", regs->intNo);
}
