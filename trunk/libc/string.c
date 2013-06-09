#include "string.h"

void *memcpy(void *restrict dst, const void *restrict src, size_t len)
{
	char *dt = (char*)dst;
	char *sc = (char*)src;
	while(len--)
		*dt++ = *sc++;
	return dst;
}

void *memset(void * dst, int val, size_t len)
{
	char *dt = (char*)dst;
	while(len--)
		*dt++ = (char)val;
	return dst;
}

char *strcpy(char *restrict dest, const char *restrict src)
{
	char * dt = dest;
	while((*dest++ = *src++));
	return dt;
}

size_t strlen(const char * s)
{
	size_t i;
	for (i = 0; s[i] != '\0'; i++) ;
	return i;
}