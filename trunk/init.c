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
extern void hltLoop();

//This function is called by the assembler code provided in init.s
void init()
{
	//TODO print out extern kernelStart and extern kernelEnd to check if this works right
	for(;;);
	hltLoop();
}