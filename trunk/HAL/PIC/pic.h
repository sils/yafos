/* HAL/PIC/pic.h
 * 
 * Provides functions for using the programmable interval controller (PIC).
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

void remapIrqs(void);

#include <sys/io.h>
#include <IDT/idt.h>

#ifndef IRQ0
	#warning "IRQ0 undefined! Should be defined in HAL/IDT/idt.h and is needed\
		in HAL/PIC/pic.h. Defining it now with standard value 0x20 (32)."
	#define IRQ0 0x20
#endif

#endif /* _PIC_H */