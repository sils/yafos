/* cpuInfo.h
 *
 * Provides functions to get information about the CPU.
 * 
 * Copyright (C) 2013 Lasse Schuirmann. All Rights Reserved.
 * Written by Lasse Schuirmann (lasse.schuirmann@gmail.com)
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 */

#ifndef _CPUINFO_H
#define _CPUINFO_H

#include <stdint.h>
#include <stdMacro.h>

#ifdef __i386__
STRUCT
{
	uint32_t eax, ebx, ecx, edx;
} PACKED cpuId_t;
#elif defined __x86_64__
STRUCT
{
	uint64_t eax, ebx, ecx, edx;
} PACKED cpuId_t;
#else
#error "Unsupported architecture!"
#endif

void assertCpuidSupport();
void assertLongModeSupport();
extern bool longModeSupport();
extern char *getVendor();
extern bool evalCpuidSupport();
extern cpuId_t *genCpuId(uint32_t function);

#endif /* _CPUINFO_H */
