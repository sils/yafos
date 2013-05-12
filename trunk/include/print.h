/* include/print.h
 * 
 * Provides functions to print strings and formatted strings to the screen.
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

#include <string.h>

#endif /* _PRINT_H */
