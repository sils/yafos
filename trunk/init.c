/* init.c
 * 
 * Initializes the kernel properly. That includes specificly:
 * 		TODO Set up a global descriptor table
 * 		TODO Set up a interrupt descriptor table
 * 		TODO Set up a timer for time measurement
 * 		TODO Set up memory management
 * 		TODO Set up a dispatcher and scheduler
 */

//For reading information passed from bootloader
#include <boot/boot.h>
#include <print.h>
#include <GDT/gdt.h>
#include <IDT/idt.h>
extern void hltLoop();

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