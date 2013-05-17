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

// Unsigned integer type of the result of the sizeof operator.
typedef unsigned int size_t;

/* TODO
 offsetof(type, member-designator)
 I nteger constant expression of type size_t, the value of whi*ch is the offset in bytes to the structure member (member-designator), from the beginning of its structure (type).
 
 The <stddef.h> header shall define the following types:
 
 ptrdiff_t
 Signed integer type of the result of subtracting two pointers.
 wchar_t
 Integer type whose range of values can represent distinct wide-character codes for all members of the largest character set specified among the locales supported by the compilation environment: the null character has the code value 0 and each member of the portable character set has a code value equal to its value when used as the lone character in an integer character constant.
 size_t */

#endif /* _STDDEF_H */