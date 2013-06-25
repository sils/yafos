/* errno.h
 * 
 * This file tries to follow the standardizations specified in the POSIX
 * Programmers Manual wich can be reached through
 * 		http://pubs.opengroup.org/onlinepubs/000095399/basedefs/errno.h.html
 * 
 * Copyright (C) 2013 Lasse Schuirmann. All Rights Reserved.
 * Written by Lasse Schuirmann (lasse.schuirmann@gmail.com)
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 */

#ifndef _ERRNO_H
#define _ERRNO_H

#include <stdint.h>

enum
{
	SUCCESS = 0,
	NOT_IMPLEMENTED,
	UNSUPPORTED_ARCH,
	ERANGE,
	OBJECT_PRESENT,
	ERR_IN_SUBFUNC,
	MAX_ERRNO
};

typedef uint8_t		uerr_t;
typedef int8_t		err_t;

uerr_t errno;

//halts the kernel if an error code is returned
bool assertSuccess(const err_t errCode);
//prints a readable warning message, if an error is returned
bool verify(const err_t errCode);
//returns a readable text for the given error code
char * getErrText(const err_t errCode);

#endif /* _ERRNO_H */