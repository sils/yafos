#include "init.h"

//This function is called by the assembler code provided in init.s
void init()
{
	installGdt();
	kprintf("GDT is set up properly with %x entries.\n", GDT_ENTRIES);
	installIdt();
	kprintf("IDT is set up properly with %x entries.\nActivating interrupts now...\n", IDT_ENTRIES);
	sti();
	kprintf("TODO 3: Set up a system timer.\n");
	kprintf("TODO 4: Set up a keyboard handler.\n");
	kprintf("TODO 5: Set up a memory manager.\n");
	
	//TODO print out extern kernelStart and extern kernelEnd to check if this works right
	for(;;);
	//hltLoop();
}