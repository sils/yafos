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

enum
{
	SUCCESS = 0,
	NOT_IMPLEMENTED,
	UNSUPPORTED_ARCH,
	ERANGE,
	OBJECT_PRESENT//TODO get a better name for this
};

typedef uint8_t		uerr_t;
typedef int8_t		err_t;

uerr_t errno;

//halts the kernel if an error code is returned TODO
void assertSuccess(err_t errCode);

//prints a readable warning message, if an error is returned TODO
void printErrCode(err_t errCode);

#endif /* _ERRNO_H */