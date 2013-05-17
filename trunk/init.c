#include "init.h"


//This function is called by the assembler code provided in init.s
void init()
{
	char welcomeString[] = "_             _  _____   _        __    ___    _    _   _____   _ \n\\\\           // |  ___| | |      / _|  /   \\  | \\  / | |  ___| | |\n \\\\    _    //  | |__   | |     / /   /  _  \\ |  \\/  | | |__   | |\n  \\\\  /_\\  //   |  __|  | |     | |   | |_| | | |\\/| | |  __|  |_|\n   \\\\// \\\\//    | |___  | |___  \\ \\_  \\     / | |  | | | |___   _ \n    \\/   \\/     |_____| |_____|  \\__|  \\___/  |_|  |_| |_____| |_|\n";
	
	clearScreen();
	installGdt();
	installIdt();
	sti();
	kprintf("%s\n",welcomeString);
	kprintf("Welcome to this eye-friendly white system!\n");
	
	//TODO print out extern kernelStart and extern kernelEnd to check if this works right
	hltLoop();//no polling! Halt the cpu.
}