/* errno.c
 * 
 * Provides functions to print readable messages from error codes.
 * 
 * Copyright (C) 2013 Lasse Schuirmann. All Rights Reserved.
 * Written by Lasse Schuirmann (lasse.schuirmann@gmail.com)
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 */

#include <errno.h>

#include <print.h>
#include <stdlib.h>

char errMessage[MAX_ERRNO][27] =
{
	"Unknown error code!",
	"Yet unimplemented feature!",
	"Unsupported architecture!",
	"Out of range!",
	"Object already exists!"
};

char * getErrText(const err_t errCode)
{
	if(errCode != SUCCESS)
	{
		if(ABS(errCode) < MAX_ERRNO)
		{
			return errMessage[ABS(errCode)];
		}
		return errMessage[0];
	}
}

extern inline void assertSuccess(const err_t errCode)
{
	if(errCode != SUCCESS)
	{
		fatalErr(getErrText(errCode));
	}
}

extern inline void printErrMsg(const err_t errCode)
{
	if(errCode != SUCCESS)
	{
		printErr(getErrText(errCode));
	}
}
