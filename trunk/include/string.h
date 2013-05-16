/* include/string.h
 *
 * This file tries to follow the standardizations specified in the POSIX
 * Programmers Manual wich can be reached through
 * 		http://pubs.opengroup.org/onlinepubs/7908799/xsh/string.h.html
 * 
 * Copyright (C) 2013 Lasse Schuirmann. All Rights Reserved.
 * Written by Lasse Schuirmann (lasse.schuirmann@gmail.com)
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 */

#ifndef _STRING_H
#define _STRING_H

// TODO include (when changing to POSIX conform one ;)
//#include <stddef.h>

#ifndef NULL
#define NULL 0
#endif /* NULL */

// TODO OBSOLETE
#include <stdint.h>

void strcat(char *, char *);
void strcpy(char *, char *);
uint32_t strlen(char *);
char strcmp(char *, char *);
int strtoi(char *, unsigned char);
unsigned int strtoui(char *, unsigned char);

#define upperCase(val) val-'a'+'A'
#define lowerCase(val) val-'A'+'a'
// END OF OBSOLETE

/* TODO for POSIX conformity:
void    *memccpy(void *restrict, const void *restrict, int, size_t);

void    *memchr(const void *, int, size_t);
int      memcmp(const void *, const void *, size_t);
void    *memcpy(void *restrict, const void *restrict, size_t);
void    *memmove(void *, const void *, size_t);
void    *memset(void *, int, size_t);
char    *strcat(char *restrict, const char *restrict);
char    *strchr(const char *, int);
int      strcmp(const char *, const char *); <-
int      strcoll(const char *, const char *);
char    *strcpy(char *restrict, const char *restrict);
size_t   strcspn(const char *, const char *);

char    *strdup(const char *);

char    *strerror(int);

int     *strerror_r(int, char *, size_t);

size_t   strlen(const char *);
char    *strncat(char *restrict, const char *restrict, size_t);
int      strncmp(const char *, const char *, size_t);
char    *strncpy(char *restrict, const char *restrict, size_t);
char    *strpbrk(const char *, const char *);
char    *strrchr(const char *, int);
size_t   strspn(const char *, const char *);
char    *strstr(const char *, const char *);
char    *strtok(char *restrict, const char *restrict);

char    *strtok_r(char *, const char *, char **);

size_t   strxfrm(char *restrict, const char *restrict, size_t);
*/

#endif /* _STRING_H */