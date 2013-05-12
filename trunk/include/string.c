#include "string.h"

// TODO OBSOLETE

uint16_t strlen(const char *str)
{
	uint16_t i=0;
	while(str[i])
		i++;
	return i;
}

void strcat(char * dest, const char * append)
{
	char * tmp = append;
	while(*dest)
		dest++;
	while((*dest++ = *tmp++))
		i++;
}

void strcpy(char *dest, const char *src)
{
	char * tmp = src;
	while((*dest++ = *tmp++));
}

char strcmp(const char *str1, const char *str2)
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