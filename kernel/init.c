#include "init.h"

//This function is called by the assembler code provided in init.s
void init(multiBoot * mbStruct)
{
	//TODO think about ways of storing strings and setting a standard language and so on.
	//Would be nice to have this on kernel level ;)
	char welcomeString[] = "_             _  _____   _        __    ___    _    _   _____   _ \n\\\\           // |  ___| | |      / _|  /   \\  | \\  / | |  ___| | |\n \\\\    _    //  | |__   | |     / /   /  _  \\ |  \\/  | | |__   | |\n  \\\\  /_\\  //   |  __|  | |     | |   | |_| | | |\\/| | |  __|  |_|\n   \\\\// \\\\//    | |___  | |___  \\ \\_  \\     / | |  | | | |___   _ \n    \\/   \\/     |_____| |_____|  \\__|  \\___/  |_|  |_| |_____| |_|\n";
	
	clearScreen();
	installGdt();
	initStdTimer(IRQ_0_FREQ);
	registerTimerHandler(IRQ0);//TODO move this to initStdTimer
	installIdt();
	registerKbdHandler(IRQ1);
	kprintf("%s",welcomeString);
	kprintf("...to this eco-friendly green system!\n");
	kprintf("\n--- WHAT WORKS RIGHT NOW ---\n");
	kprintf("- Global descriptor table\n");
	kprintf("- Interrupt descriptor table\n");
	kprintf("- Time measuring\n");
	kprintf("- Beeping\n");
	#ifdef DEBUG
	kprintf("\n--- FOR DEBUG PURPOSES ---\n");
	kprintf("MEMORY MANAGER:\nInitialize:\n");
	pMemInit();
	kprintf("Initialization complete.\n");
	printAllocMem();
	pMemAlloc(3);
	uintptr_t tmp = pMemAlloc(32);
	pMemAlloc(1);
	printAllocMem();
	pMemFreeAdv(tmp, 3);
	printAllocMem();
	#endif
	
	sti();
	
	for(;;)
	{
		hlt();
	}
}
