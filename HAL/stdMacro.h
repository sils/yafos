/* stdMacro.h
 * 
 * Provides some macros for general use.
 * 
 * Copyright (C) 2013 Lasse Schuirmann. All Rights Reserved.
 * Written by Lasse Schuirmann (lasse.schuirmann@gmail.com)
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 */

#ifndef _STDMACRO_H
#define _STDMACRO_H

//For structs, lets use typedefs
#define STRUCT			typedef struct
#define PACKED			__attribute__((packed))
#define PAGE_ALIGNED	__attribute__((aligned (1024)))

//Using assembly
#define ASM				__asm__ __volatile__

//sould make some things a little bit easier
#define KB				(1024)
#define MB				(1024*KB)
#define GB				(1024*MB)
#define TB				(1024*TB)

//for endless loops
#define true			1
#define TRUE			1
#define false			0
#define FALSE			0

//TODO macros for setting bits: clear, set, toggle

#endif /* _STDMACRO_H */
