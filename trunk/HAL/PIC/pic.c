#include "pic.h"

//TODO rewrite this with macros
void remapIrqs(void)
{
	//init master PIC
	//TODO test somehow if this works right since we get a double fault
	outb(0x20, 0x11); /* write ICW1 to PICM, we are gonna write commands to PICM */
	outb(0xA0, 0x11); /* write ICW1 to PICS, we are gonna write commands to PICS */
	
	outb(0x21, IRQ0); /* remap PICM to 0x20 (32 decimal) */
	outb(0xA1, IRQ0 + 0x09); /* remap PICS to 0x28 (40 decimal) */
	
	outb(0x21, 0x04); /* IRQ2 -> connection to slave */ 
	outb(0xA1, 0x02);
	
	outb(0x21, 0x01); /* write ICW4 to PICM, we are gonna write commands to PICM */
	outb(0xA1, 0x01); /* write ICW4 to PICS, we are gonna write commands to PICS */
	
	outb(0x21, 0x0); /* enable all IRQs on PICM */
	outb(0xA1, 0x0); /* enable all IRQs on PICS */
	
	//TODO read article about PIC and use macros to make this more understandable
	// remove these comments and replace with own ones
}