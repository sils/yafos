#include "init.h"

extern void* kernelStart;
extern void* kernelEnd;

//This function is called by the assembler code provided in init.s
void init()
{
	//TODO think about ways of storing strings and setting a standard language and so on.
	//Would be nice to have this on kernel level ;)
	char welcomeString[] = "_             _  _____   _        __    ___    _    _   _____   _ \n\\\\           // |  ___| | |      / _|  /   \\  | \\  / | |  ___| | |\n \\\\    _    //  | |__   | |     / /   /  _  \\ |  \\/  | | |__   | |\n  \\\\  /_\\  //   |  __|  | |     | |   | |_| | | |\\/| | |  __|  |_|\n   \\\\// \\\\//    | |___  | |___  \\ \\_  \\     / | |  | | | |___   _ \n    \\/   \\/     |_____| |_____|  \\__|  \\___/  |_|  |_| |_____| |_|\n";
	
	clearScreen();
	installGdt();
	//initTimer(100);
	installIdt();
	kprintf("%s\n\n",welcomeString);
	kprintf("Welcome to this eco-friendly green system!\n");
	sti();
	
	kprintf("Kernel size: %u pages\n", ((uint32_t)&kernelEnd - (uint32_t)&kernelStart)/0x1000);
	for(;;)
	{
		hlt();
	}
}
