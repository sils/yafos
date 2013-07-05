/* paging.h
 * 
 * Header file for paging.
 *
 * Copyright (C) 2013 Lasse Schuirmann. All Rights Reserved.
 * Written by Lasse Schuirmann (lasse.schuirmann@gmail.com)
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 */

#ifndef _PAGING_H
#define _PAGING_H

#include <stdint.h>
#include <errno.h>

//TODO provide a possibility to map the page tables used by the kernel to the
//programs

void initPaging();
uint32_t loadPageTable();
void setPageDir(void *pDir);
err_t mapPage(uintptr_t physicalAddr, uintptr_t virtualAddr);
err_t mapRegion(uintptr_t physicalStart, uintptr_t virtualStart,
				uintptr_t physicalEnd);
//TODO unmap

#ifdef __i386__
#define _X86_PAGING_H
#else
#error "Unsupported architecture."
#endif

#endif /* _PAGING_H */
