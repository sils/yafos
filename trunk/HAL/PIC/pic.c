#include "pic.h"

//TODO rewrite this with macros
void remapIrqs(void)
{
	//TODO test somehow if this works right since we get a double fault
	PIC_MASTER_CMD(0x11);
	PIC_SLAVE_CMD(0x11);
	
	outb(0x21, PIC_MASTER_OFFS);
	outb(0xA1, PIC_SLAVE_OFFS);
	
	outb(0x21, 0x04); /* IRQ2 -> connection to slave */ 
	outb(0xA1, 0x02);
	
	outb(0x21, 0x01); /* write ICW4 to PICM, we are gonna write commands to PICM */
	outb(0xA1, 0x01); /* write ICW4 to PICS, we are gonna write commands to PICS */
	
	outb(0x21, 0x0); /* enable all IRQs on PICM */
	outb(0xA1, 0x0); /* enable all IRQs on PICS */
	
	//TODO read article about PIC and use macros to make this more understandable
	// remove these comments and replace with own ones
}