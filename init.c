#include "init.h"

extern int kernelStart;
extern int kernelEnd;

//This function is called by the assembler code provided in init.s
void init()
{
	//TODO find a way to store this more intellegently
	char welcomeString[] = "_             _  _____   _        __    ___    _    _   _____   _ \n\\\\           // |  ___| | |      / _|  /   \\  | \\  / | |  ___| | |\n \\\\    _    //  | |__   | |     / /   /  _  \\ |  \\/  | | |__   | |\n  \\\\  /_\\  //   |  __|  | |     | |   | |_| | | |\\/| | |  __|  |_|\n   \\\\// \\\\//    | |___  | |___  \\ \\_  \\     / | |  | | | |___   _ \n    \\/   \\/     |_____| |_____|  \\__|  \\___/  |_|  |_| |_____| |_|\n";
	//TODO find nice and friendly standard colours
	clearScreen();
	installGdt();
	//initTimer(100);
	installIdt();
	kprintf("%s\n",welcomeString);
	//think about ways of storing strings and setting a standard language and so on.
	//Would be nice to have this on kernel level ;)
	kprintf("Welcome to this eco-friendly green system! (Yeeees... it liiiives!)\n");
	sti();
	kprintf("Well, nobody knows why - but here cooooomes: THE DOUBLE FAULT!\n");
	
	//TODO print out extern kernelStart and extern kernelEnd to check if this works right
	kprintf("kernelStart: %x\nkernelEnd:   %x\n",kernelStart,kernelEnd);
	hltLoop();//no polling! Halt the cpu.
}