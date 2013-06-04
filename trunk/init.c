#include "init.h"

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
	kprintf("Masking IRQs...\n");
	maskIrqs(0xFFFF);
	sti();
	callint20;
	callint3;
	callint13;
	callint8;
	
	kprintf("Kernel size: %x pages\n", ((uint32_t)KERNEL_END - (uint32_t)KERNEL_START)/0x1000);
	for(;;)
	{
		hlt();
	}
}
