#include "string.h"

// TODO OBSOLETE make it independent of stdint.h and POSIX conform

uint32_t strlen(char *str)
{
	uint32_t i=0;
	while(str[i])
		i++;
	return i;
}

void strcat(char * dest, char * append)
{
	while(*dest)
		dest++;
	while((*dest++ = *append++));
}

void strcpy(char *dest, char *src)
{
	while((*dest++ = *src++));
}

char strcmp(char *str1, char *str2)
{
	while((*str1 == *str2) && *str1 && str2)
	{
		str1++;
		str2++;
	}
	if(*str1 == *str2)
		return 1;
	return 0;
}

uint8_t charToDigit(char val)
{
	if(val > 'a')
		return val-'a'+10;
	if(val > 'A')
		return val-'A'+10;
	if(val > '0')
		return val-'0';
	return 0;
}

int strtoi(char *str, unsigned char base)
{
	char fact;
	int val;
	unsigned char i;
	i=0;
	fact=1;
	val=0;
	if(str[i]=='-')
	{
		i++;
		fact=-1;
	}
	while(str[i])
	{
		val*=base;
		val+=charToDigit(str[i]);
		i++;
	}
	return fact*val;
}

unsigned int strtoui(char *str, unsigned char base)
{
	unsigned char i;
	i=0;
	unsigned int val;
	val=0;
	while(str[i])
	{
		val*=base;
		val+=charToDigit(str[i]);
		i++;
	}
	return val;
}

// TODO OBSOLETE