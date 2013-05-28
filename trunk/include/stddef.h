/* include/stddef.h
 * 
 * This file tries to follow the standardizations specified in the POSIX
 * Programmers Manual wich can be reached through
 * 		http://pubs.opengroup.org/onlinepubs/009696799/basedefs/stddef.h.html
 * 
 * Copyright (C) 2013 Lasse Schuirmann. All Rights Reserved.
 * Written by Lasse Schuirmann (lasse.schuirmann@gmail.com)
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 */

#ifndef _STDDEF_H
#define _STDDEF_H

#ifndef NULL
#define NULL 0
#endif /* NULL */

//Standard integer is assumed as 32 bit integer on a 32 bit platform.

// Unsigned integer type of the result of the sizeof operator.
typedef unsigned int	size_t;

// Integer capable of holding the difference of two pointers.
//  (wich can also be 1<<32 - 0x0 -> result with an ordinary integer: overflow)
typedef long int		ptrdiff_t;

// Integer for holding all implemented types of character codes. Currently this
//  isn't much ;) later it grows.
typedef unsigned char	wchar_t;

/* TODO
 offsetof(type, member-designator)
 Integer constant expression of type size_t, the value of which is the offset
 in bytes to the structure member (member-designator), from the beginning of
 its structure (type).
 */

#endif /* _STDDEF_H */