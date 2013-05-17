/* HAL/GDT/gdt.h
 * 
 * Provides function headers for manipulating the global descriptor table.
 * See http://wiki.osdev.org/Global_Descriptor_Table for more information about
 * the structure.
 * 
 * Copyright (C) 2013 Lasse Schuirmann. All Rights Reserved.
 * Written by Lasse Schuirmann (lasse.schuirmann@gmail.com)
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 */

#ifndef _GDT_H
#define _GDT_H
//TODO test it with switching code and data segments andinvoking wrong interrupts

#include <stdint.h>

typedef struct
{
	uint16_t limitLow;
	uint16_t baseLow;
	uint8_t  baseMid;
	uint8_t  access;
	uint8_t  granularity;
	uint8_t  baseHigh;
}__attribute__((packed)) gdtEntry;

typedef struct
{
	uint16_t limit;
	void    *base;
}__attribute__((packed)) gdtPtr;

#define GDT_ENTRIES 3
void installGdt(void);
gdtEntry gdt[GDT_ENTRIES];
gdtPtr   tgdtPtr;

// See http://wiki.osdev.org/Global_Descriptor_Table for more information
#define G_ACCESSED_BIT	0x01
#define G_RW_BIT		0x02
#define G_EXP_DIR_BIT	0x04
#define G_EXEC_BIT		0x08
#define G_CODEDATA_BIT	0x10//if unset this is for other use than code or data
#define G_DPL_BITS(dpl)	((dpl)<<5) //bits 5 and 6
#define G_PRESENT_BIT	0x80

#define G_LIMIT_BITS(a)	(((a) >> 15) & 0xF) //(a<<16)>>8, 4 bits
#define G_AVAIL_BIT		0x10
#define G_LONG_BIT		0x20 //only for 64 bit mode!!!
#define G_32_BIT		0x40
#define G_GRAN_BIT		0x80

#define SET_CODE_GATE(index, addr, limit, dpl)\
	gdtSetGate((index), (addr), (limit),\
	G_PRESENT_BIT | G_CODEDATA_BIT | G_DPL_BITS(dpl) | G_RW_BIT | G_EXEC_BIT,\
	G_GRAN_BIT | G_32_BIT | G_GRAN_BIT)
 #define SET_DATA_GATE(index, addr, limit, dpl)\
	gdtSetGate((index), (addr), (limit),\
	G_PRESENT_BIT | G_CODEDATA_BIT | G_DPL_BITS(dpl) | G_RW_BIT,\
	G_GRAN_BIT | G_32_BIT | G_GRAN_BIT)
#define SET_ZERO_GATE(index)					gdtSetGate((index),0,0,0,0)

#include <sys/io.h>

#endif /* _GDT_H */