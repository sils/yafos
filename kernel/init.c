#include "init.h"

//This function is called by the assembler code provided in init.s
void init()
{
	//TODO think about ways of storing strings and setting a standard language and so on.
	//Would be nice to have this on kernel level ;)
	char welcomeString[] = "_             _  _____   _        __    ___    _    _   _____   _ \n\\\\           // |  ___| | |      / _|  /   \\  | \\  / | |  ___| | |\n \\\\    _    //  | |__   | |     / /   /  _  \\ |  \\/  | | |__   | |\n  \\\\  /_\\  //   |  __|  | |     | |   | |_| | | |\\/| | |  __|  |_|\n   \\\\// \\\\//    | |___  | |___  \\ \\_  \\     / | |  | | | |___   _ \n    \\/   \\/     |_____| |_____|  \\__|  \\___/  |_|  |_| |_____| |_|\n";
	
	clearScreen();
	installGdt();
	initStdTimer(IRQ_0_FREQ);
	registerTimerHandler(IRQ0);//TODO move this to initStdTimer
	installIdt();
	pMemInit();
	registerKbdHandler(IRQ1);
	kprintf("%s",welcomeString);
	kprintf("...to this eco-friendly green system!\n");
	kprintf("\n--- WHAT WORKS RIGHT NOW ---\n");
	kprintf("- Global descriptor table\n");
	kprintf("- Interrupt descriptor table\n");
	kprintf("- Time measuring\n");
	kprintf("- Beeping\n");
	kprintf("- Physical memory management\n");
	
	sti();
	
	#ifdef DEBUG
	kprintf("\n--- FOR DEBUG PURPOSES ---\n");
	
	kprintf("TESTING PAGING:\n");
	
	kprintf("[PAG] Acitvating paging...\n");
	initPaging();
	
	//map framebuffer memory
	if((errno = -mapPage(0xB8000, FB_MEM_LOCATION)) != 0)
	{
		kprintf("[ERR] mapPage returned %u.\n", errno);
	}
	
	
	uintptr_t addr = (uintptr_t)KERNEL_START;
	for(; addr < (uintptr_t)KERNEL_END; addr += PAGE_SIZE)
	{
		if((errno = -mapPage(addr, addr)) != 0)
		{
			kprintf("[ERR] mapPage returned %u.\n", errno);
		}
	}
	loadPageTable();
	kprintf("[PAG] Done.\n");
	
	kprintf("[PAG] Generating page fault...\n");
	int *i = (void*)0x2000000;
	*i = 5;
	
	#endif
	
	for(;;)
	{
		hlt();
	}
}
