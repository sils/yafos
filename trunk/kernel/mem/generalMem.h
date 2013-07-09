/* generalMem.h
 * 
 * Provides a general memory manager for managing. This is kind of a 'class'.
 * It uses the next fit algorithm.
 * 
 * Every offset or size is measured in pages.
 *
 * Copyright (C) 2013 Lasse Schuirmann. All Rights Reserved.
 * Written by Lasse Schuirmann (lasse.schuirmann@gmail.com)
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 */

#ifndef _GENERALMEM_H
#define _GENERALMEM_H

#include <stdMacro.h>
#include <stdint.h>

STRUCT
{
	uint32_t *bitmap;
	uint32_t bitmapSize;
	uint32_t lastFreeIndex;
} genmem_t;

void genMemInit(genmem_t *obj);
void genMemFreeAdv(genmem_t *obj, const uintptr_t addr, uint32_t count);
void * genMemAlloc(genmem_t *obj, const uint32_t count);

#endif /* _GENERALMEM_H */
