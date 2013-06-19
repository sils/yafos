/* multiboot.h
 * 
 * Defines nessecary structures for reading information passed by multiboot
 * compliant bootloaders. See
 * 		http://www.gnu.org/software/grub/manual/multiboot/multiboot.pdf
 * for more information.
 *
 * Copyright (C) 2013 Lasse Schuirmann. All Rights Reserved.
 * Written by Lasse Schuirmann (lasse.schuirmann@gmail.com)
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 */

#ifndef _MULTIBOOT_H
#define _MULTIBOOT_H

#include <stdint.h>
#include <stdMacro.h>
#include <settings.h>

//defined by linker script
extern uint8_t kernelStart;
extern uint8_t kernelEnd;
#define KERNEL_START	&kernelStart
#define KERNEL_END		&kernelEnd

#if ARCH != 32
#warning "[ERROR] For 64 architecture some fusions are to be made!"
#endif /* ARCH == 32 */

STRUCT
{
	uint32_t size;
	//join this too
	uint32_t baseLow;
	uint32_t baseHigh;
	//join this in 64 bit
	uint32_t lengthLow;
	uint32_t lengthHigh;
	//if type==1 it's freely available
	uint32_t type;
} PACKED mMap;

STRUCT
{
	uint32_t	flags;
	uint32_t	memLower;
	uint32_t	memUpper;
	uint32_t	bootDevice;
	uint32_t	cmdLine;
	uint32_t	modsCount;
	void *		modsAddr;
	uint32_t	syms[4];
	uint32_t	mMapLength;
	mMap *		mMapAddr;
	//further information is not needed for now
	//if needed: look at the mentioned pdf at page 11.
} PACKED multiBoot;

#define MB_MEM_SET(flags)	(flags & 0b0000001)
#define MB_DEV_SET(flags)	(flags & 0b0000010)
#define MB_CMD_SET(flags)	(flags & 0b0000100)
#define MB_MODS_SET(flags)	(flags & 0b0001000)
#define MB_SYMS_SET(flags)	(flags & 0b0110000)
#define MB_MMAP_SET(flags)	(flags & 0b1000000)

//for MIN/MAX
#include <stdlib.h>
#include <print.h>

#endif /* _MULTIBOOT_H */
