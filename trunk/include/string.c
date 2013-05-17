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
