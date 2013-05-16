/* include/print.h
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

// puts a char (white on black) to the screen
#define putChar(toput) put((toput), 0x0f)


#define NEWLN	'\n'
#define BLANK	' '
#define BACKSP	'\b'

#include <string.h>

#endif /* _PRINT_H */
