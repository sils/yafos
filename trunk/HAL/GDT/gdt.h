/* HAL/GDT/gdt.h
 * 
 * Provides function headers for manupulating the global descriptor table.
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

typedef struct
{
	uint16_t limitLow;
	uint16_t baseLow;
	uint8_t  baseMid;
	uint16_t flags;
	uint8_t  baseHigh;
}__attribute__((packed)) gdtEntry;

typedef struct
{
	uint16_t limit;
	gdtEntry *base;
}__attribute__((packed)) gdtPtr;

void installGdt(void);

#define GDT_ENTRIES 3
gdtEntry globalGdt[GDT_ENTRIES];
gdtPtr   globalGdtPtr;

extern void loadGdt();//TODO use inline assembly

#define SET_CODE_GATE(baseAddr, limit)	gdtSetGate((baseAddr),(limit),CODEDATA_BIT | RW_BIT | GRAN_BIT | _32_BIT | GRAN_BIT | EXEC_BIT)
#define SET_DATA_GATE(baseAddr, limit)	gdtSetGate((baseAddr),(limit),CODEDATA_BIT | RW_BIT | GRAN_BIT | _32_BIT | GRAN_BIT)
#define SET_ZERO_GATE()					gdtSetGate(0,0,0)

#endif /* _GDT_H */