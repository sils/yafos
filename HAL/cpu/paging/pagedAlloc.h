/* pagedAlloc.h
 * 
 * For getting memory that is guaranteed mapped.
 *
 * Copyright (C) 2013 Lasse Schuirmann. All Rights Reserved.
 * Written by Lasse Schuirmann (lasse.schuirmann@gmail.com)
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 */

#ifndef _PAGEDALLOC_H
#define _PAGEDALLOC_H

#include <stdint.h>

void pagedMemInit(uint32_t size);
void *pagedMemAlloc(const uint8_t count);
void pagedMemFree(const uintptr_t addr, uint8_t count);

#endif /* _PAGEDALLOC_H */
