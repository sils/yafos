/* HAL/GDT/gdt.h
 * 
 * Provides function headers for manupulating the global descriptor table.
 */

#ifndef _GDT_H
#define _GDT_H

#include <stdint.h>

typedef struct
{
	unsigned limitLow	:16;
	unsigned baseLow	:16;
	unsigned baseMid	:8;
	unsigned accessed	:1;//should be initialized wit zero
	unsigned type		:4;
	unsigned privilege	:2;
	unsigned present	:1;
	unsigned limitHigh	:4;
	unsigned avail		:1;
	unsigned longmode	:1;//0 for protected mode ;)
	unsigned size		:1;
	unsigned granularity:1;
	unsigned baseHigh	:8;
}__attribute__((packed)) gdtEntry;

typedef struct
{
	uint16_t limit;
	gdtEntry *base;
}__attribute__((packed)) gdtPtr;

void installGdt(void);

#endif /* _GDT_H */