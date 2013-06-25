/* gdt.h
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

#include <stdint.h>
#include <stdMacro.h>

STRUCT
{
	uint16_t limitLow;
	uint16_t baseLow;
	uint8_t  baseMid;
	uint8_t  access;
	uint8_t  granularity;
	uint8_t  baseHigh;
} PACKED gdtEntry_t;

STRUCT
{
	uint16_t limit;
	void    *base;
} PACKED gdtPtr_t;

#define GDT_ENTRIES 3
void installGdt(void);
gdtEntry_t gdt[GDT_ENTRIES];
gdtPtr_t   tgdtPtr;

// See http://wiki.osdev.org/Global_Descriptor_Table for more information
#define G_ACCESSED	0x01
#define G_RW		0x02
#define G_EXP_DIR	0x04
#define G_EXEC		0x08
#define G_CODEDATA	0x10//if unset this is for other use than code or data
#define G_DPL(dpl)	((dpl)<<5)	//bits 5 and 6
#define G_PRESENT	0x80

#define G_LIMIT(a)	(((a) >> 15) & 0xF)	//(a<<16)>>8, 4 bits
#define G_AVAIL		0x10
#define G_LONG		0x20				//only for 64 bit mode!!!
#define G_32		0x40
#define G_GRAN		0x80

#define SET_CODE_GATE(index, addr, limit, dpl)\
	gdtSetGate((index), (addr), (limit),\
	G_PRESENT | G_CODEDATA | G_DPL(dpl) | G_RW | G_EXEC,\
	G_GRAN | G_32 | G_GRAN)
 #define SET_DATA_GATE(index, addr, limit, dpl)\
	gdtSetGate((index), (addr), (limit),\
	G_PRESENT | G_CODEDATA | G_DPL(dpl) | G_RW,\
	G_GRAN | G_32 | G_GRAN)
#define SET_ZERO_GATE(index)					gdtSetGate((index),0,0,0,0)

extern void jumpToSegment(uint8_t dataSegment, uint8_t codeSegment);
#include <sys/io.h>

#endif /* _GDT_H */