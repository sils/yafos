#include "init.h"

//This function is called by the assembler code provided in init.s
void init()
{
	kprintf("TODO 1: Set up a GDT.\n");
	kprintf("TODO 2: Set up a IDT.\n");
	kprintf("TODO 3: Set up a system timer.\n");
	kprintf("TODO 4: Set up a keyboard handler.\n");
	kprintf("TODO 5: Set up a memory manager.\n");
	//TODO print out extern kernelStart and extern kernelEnd to check if this works right
	for(;;);
	hltLoop();
}