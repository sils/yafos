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
	//TODO move the whole paging initialization stuff to some subfile
	initPaging();
	
	uintptr_t addr = (uintptr_t)KERNEL_START;
	for(; addr < (uintptr_t)KERNEL_END; addr += PAGE_SIZE)
	{
		assertSuccess(mapPage(addr, addr));
	}
	
	//map framebuffer memory
	assertSuccess(mapPage(0xB8000, FB_MEM_LOCATION));
	loadPageTable();//*/
	
	clearScreen();
	
	kprintf("%s",welcomeString);
	kprintf("...to the blue ocean!\n\n");
	kprintf("\n            _../|_\n");
	kprintf("          ='__  _~-.\n");
	kprintf("              \\'  ~-`\\._\n");
	kprintf("                    |/~`\n");
	kprintf("   .    .    .    .    .    .    .\n");
	kprintf("_.`(._.`(._.`(._.`(._.`(._.`(._.`(.\n\n");
	
	printDebug("--- WHAT WORKS RIGHT NOW ---");
	printDebug("- Global descriptor table");
	printDebug("- Interrupt descriptor table");
	printDebug("- Time measuring");
	printDebug("- Beeping");
	printDebug("- Physical memory management");
	printDebug("- Paging");
	
	assertCpuidSupport();
	
	printMsg("Testing memory manager...");
	void * tmp;
	printMsg(" Got  %u pages at %x", 4, tmp= pMemAlloc(4));
	printMsg(" Got  %u pages at %x", 4, pMemAlloc(4));
	printMsg(" Got  %u pages at %x", 400, pMemAlloc(400));
	printMsg(" Free %u pages at %x", 10, tmp);
	pMemFreeAdv((uintptr_t)tmp,10);
	printMsg(" Got  %u pages at %x", 4, pMemAlloc(4));
	printMsg(" Got  %u pages at %x", 4, pMemAlloc(4));
	printMsg(" Got  %u pages at %x", 4, pMemAlloc(4));
	
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
