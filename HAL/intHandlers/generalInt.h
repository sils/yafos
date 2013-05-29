/* HAL/intHandlers/generalInt.h
 * 
 * Provides the general interrupt handler.
 * 
 * Copyright (C) 2013 Lasse Schuirmann. All Rights Reserved.
 * Written by Lasse Schuirmann (lasse.schuirmann@gmail.com)
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 */

#ifndef _GENERAL_INT_H
#define _GENERAL_INT_H

//these messages use 2 pages in space (about 0x2000 bytes)
char exceptionMessage[16][28] = {
	"Division by zero occurred.",
	"Single step",
	"Non maskable interrupt",
	"Breakpoint",
	"Overflow",
	"Bounds check",
	"Undefined OP Code!",
	"No coprocessor",
	"Double fault!",
	"Coprocessor segment overrun",
	"Invalit TSS!",
	"Segment not present.",
	"Task segment overrun",
	"General protection fault!",
	"Page fault!",
	"Unassigned"
};

#include <cpu/registers.h>
#include <print.h>
#include <PIC/pic.h>

#endif /* _GENERAL_INT_H */
