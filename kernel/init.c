#include "init.h"

//This function is called by the assembler code provided in init.s
void init()
{
	//TODO think about ways of storing strings and setting a standard language and so on.
	//Would be nice to have this on kernel level ;)
	char welcomeString[] = "_             _  _____   _        __    ___    _    _   _____   _ \n\\\\           // |  ___| | |      / _|  /   \\  | \\  / | |  ___| | |\n \\\\    _    //  | |__   | |     / /   /  _  \\ |  \\/  | | |__   | |\n  \\\\  /_\\  //   |  __|  | |     | |   | |_| | | |\\/| | |  __|  |_|\n   \\\\// \\\\//    | |___  | |___  \\ \\_  \\     / | |  | | | |___   _ \n    \\/   \\/     |_____| |_____|  \\__|  \\___/  |_|  |_| |_____| |_|\n";
	
	installGdt();
	initStdTimer(IRQ_0_FREQ);
	registerTimerHandler(IRQ0);//TODO move this to initStdTimer
	installIdt();
	pMemInit();
	registerKbdHandler(IRQ1);
	sti();
	//TODO move the whole paging initialization stuff to some subfile
	initPaging();
	//map framebuffer memory
	if((errno = -mapPage(0xB8000, FB_MEM_LOCATION)) != 0)
	{
		fatalErr("Failed mapping %x to %x. Error code: %u.", 0xB8000,
				 FB_MEM_LOCATION, errno);
	}
	
	uintptr_t addr = (uintptr_t)KERNEL_START;
	for(; addr < (uintptr_t)KERNEL_END; addr += PAGE_SIZE)
	{
		if((errno = -mapPage(addr, addr)) != 0)
		{
			fatalErr("Failed mapping %x to %x. Error code: %u.", addr,
				 addr, errno);
		}
	}
	loadPageTable();
	
	clearScreen();
	
	kprintf("%s",welcomeString);
	kprintf("...to this amazingly blue system!\n\n");
	
	printDebug("--- WHAT WORKS RIGHT NOW ---");
	printDebug("- Global descriptor table");
	printDebug("- Interrupt descriptor table");
	printDebug("- Time measuring");
	printDebug("- Beeping");
	printDebug("- Physical memory management");
	printDebug("- Paging");
	
	#ifdef DEBUG
	printMsg("Generating page fault...");
	int *i = (void*)0x2000000;
	*i = 5;
	#endif
	
	for(;;)
	{
		hlt();
	}
}
