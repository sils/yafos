/* cmos.h
 * 
 * Provides functions to read and write abstract data to the CMOS.
 * 
 * Copyright (C) 2013 Lasse Schuirmann. All Rights Reserved.
 * Written by Lasse Schuirmann (lasse.schuirmann@gmail.com)
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 */

#ifndef _CMOS_H
#define _CMOS_H

#include <time.h>
#include <stdint.h>

struct tm getCmosTime();//TODO
//TODO some macros

#include <sys/io.h>

#endif /* _CMOS_H */
