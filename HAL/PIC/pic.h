/* pic.h
 * 
 * Provides functions for using the programmable interval controller (PIC).
 * See http://www.lowlevel.eu/wiki/PIC for more information.
 * 
 * Copyright (C) 2013 Lasse Schuirmann. All Rights Reserved.
 * Written by Lasse Schuirmann (lasse.schuirmann@gmail.com)
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 */

#ifndef _PIC_H
#define _PIC_H

#include <stdint.h>
#include <cpu/IDT/idt.h>

#ifndef IRQ0
	#warning "IRQ0 undefined! Should be defined in HAL/IDT/idt.h and is needed\
		in HAL/PIC/pic.h. Defining it now with standard value 0x20 (32)."
	#define IRQ0 0x20
#endif

void remapIrqs(void);
void maskIrqs(uint16_t mask);
#define endInterrupt(intNo)	(intNo)<IRQ8\
		? PIC_MASTER_CMD(PIC_EOI)\
		: PIC_SLAVE_CMD(PIC_EOI)

#define PIC_MASTER_CMD(cmd)	outb(PIC_MASTER_CMD_B, (cmd))
#define PIC_SLAVE_CMD(cmd)	outb(PIC_SLAVE_CMD_B , (cmd))
#define PIC_MASTER_DAT(cmd)	outb(PIC_MASTER_DAT_B, (cmd))
#define PIC_SLAVE_DAT(cmd)	outb(PIC_SLAVE_DAT_B , (cmd))

//
// CONSTANTS
//

//useful things
#define PIC_MASTER_CMD_B	0x20
#define PIC_SLAVE_CMD_B		0xA0
#define PIC_MASTER_DAT_B	PIC_MASTER_CMD_B+1
#define PIC_SLAVE_DAT_B 	PIC_SLAVE_CMD_B+1

//end of interrupt
#define PIC_EOI				0x20

//ICW1
#define PIC_ICW4_FOLLOWS	1
#define PIC_SINGLE_MODE		2
#define PIC_INIT			0x10
//ICW2
#define PIC_MASTER_OFFS		IRQ0
#define PIC_SLAVE_OFFS		PIC_MASTER_OFFS+0x08
//ICW3
#define PIC_SLAVE_IRQ		4
#define PIC_MASTER_IRQ		2
//ICW4
#define PIC_PC				1
#define PIC_AUTO_EOI		1<<1


#include <sys/io.h>
#include <intHandlers/generalInt.h>

#endif /* _PIC_H */
