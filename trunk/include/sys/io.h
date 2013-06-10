/* io.h
 * 
 * Provides functions for general input and output. (Writing to registers ...)
 * 
 * Copyright (C) 2013 Lasse Schuirmann. All Rights Reserved.
 * Written by Lasse Schuirmann (lasse.schuirmann@gmail.com)
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 */

#ifndef _IO_H
#define _IO_H

#include <stdint.h>

//most general
#define hlt()			__asm__ __volatile__ ("hlt")

//interrupts
#define cli()			__asm__ __volatile__ ("cli")
#define sti()			__asm__ __volatile__ ("sti")
#define nop()			__asm__ __volatile__ ("nop")
#define callint8		__asm__ __volatile__ ("int $0x08")
#define callint13		__asm__ __volatile__ ("int $0x13")
#define callint20		__asm__ __volatile__ ("int $0x20")
#define callint3		__asm__ __volatile__ ("int $0x03") //TODO lets call user specified interrupt ;)

//load tables
#define lidt(idtptr)	__asm__ __volatile__("lidt %0" : : "m" (idtptr));
#define lgdt(gdtptr)	__asm__ __volatile__("lgdt %0" : : "m" (gdtptr));

void outb(uint16_t port, uint8_t value);
uint8_t inb (uint16_t);

#endif /* _IO_H */
