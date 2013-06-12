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
#define STRUCT		typedef struct
#define PACKED		__attribute__((packed))

//Using assembly
#define ASM			__asm__ __volatile__

#endif /* _STDMACRO_H */
