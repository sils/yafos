/* print.h
 * 
 * Provides functions to print strings and formatted strings to the screen.
 * This file is an addition to the posix library for kernel debugging purpposes.
 * 
 * Copyright (C) 2013 Lasse Schuirmann. All Rights Reserved.
 * Written by Lasse Schuirmann (lasse.schuirmann@gmail.com)
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 */

#ifndef _PRINT_H
#define _PRINT_H

#include <stdint.h>
#include <stdarg.h>

// kernel version of printf
void kprintf(const char *, ...);
// puts a colored char to the screen
void put(const unsigned char, const uint8_t);
// prints a string to the screen
void print(char *);
// clears the screen ;)
void clearScreen();

// puts a char (white on black) to the screen
#define putChar(toput) put((toput), STDCOL)

//special signs
#define NEWLN	'\n'
#define BLANK	' '
#define BACKSP	'\b'

//TODO find nice and friendly standard colors wich are used for the whole system
//standard colors
#define STDBG	T_GREEN
#define STDFG	T_WHITE
#define STDCOL	COLCODE(STDFG, STDBG)

//color
#define T_BLACK		0
#define T_BLUE		1
#define T_GREEN		2
#define T_CYAN		3
#define T_RED		4
#define T_MAGENTA	5
#define T_BROWN		6
#define T_LIGHTGRAY	7
#define T_WHITE		T_LIGHT(T_LIGHTGRAY)

#define COLCODE(fore, back) (((back)<<4) + (fore))

#define T_LIGHT(col) ((col)+0x8)

#define GET_POS(x,y)	((y)*80 + (x))

#define FB_CMD		0x3D4
#define FB_DATA		0x3D5
#define FB_HIGH_B	14
#define FB_LOW_B	15

#define FB_LINES	25
#define FB_COLUMNS	80

#define FB_MEM_LOCATION	0xB8000

#include <string.h>
#include <sys/io.h>

#endif /* _PRINT_H */
