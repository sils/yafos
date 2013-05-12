#include "print.h"

// TODO remove this stupid function
char charDigit(const unsigned char val)
{
	if(val<10)
		return val+'0';
	return val-10+'A';
}

// TODO move this to a file where it belongs
static void uIntToStr(char *dest, uint32_t val, const uint8_t base)
{
	//at binary representation we can have max 32 digits
	char buf[33];
	uint8_t i=32;
	buf[i]=0;
	do
	{
		buf[--i] = charDigit(val % base);
		val /= base;
	}
	while(val);
	strcpy(dest, buf+i);
}

// TODO move this to a file where it belongs
static void intToStr(char *dest, const int32_t val, const uint8_t base)
{
	if(val<0)
	{
		*(dest)='-';
		uIntToStr(dest+1, (uint32_t)(-val), base);
	}
	else uIntToStr(dest, (uint32_t)val, base);
}

static void scrollUp()
{
	uint16_t i;
	volatile unsigned char *videoram = (unsigned char *)0xB8000;
	for(i=0;i<24*80*2;i++)
		videoram[i]=videoram[i+160];
	for(; i<2*25*80;i++)
	{
		if(i % 2)
			videoram[i]=0;
		else videoram[i]=' ';
	}
}

void put(const unsigned char val, const uint8_t color)
{
	static uint8_t x=0, y=0;
	volatile unsigned char *videoram = (unsigned char *)0xB8000;
	
	if(val == '\n')
	{
		x=0;
		y++;
		if(y>24)//scroll up one line
		{
			scrollUp();
			y--;
		}
		return;
	}
	
	if(val == '\b')
	{
		if(x>0)
		{
			x--;
			videoram[2*(y*80 + x)] = ' ';
			videoram[2*(y*80 + x)+1] = color;
			return;
		}
		else
			return;
	}
	
	if(x>79)
	{
		x=0;
		y++;
	}
	if(y>24)//scroll up one line
	{
		scrollUp();
		y--;
	}
	
	videoram[2*(y*80 + x)] = val;
	videoram[2*(y*80 + x)+1] = color;
	x++;
}

void print(char *str)
{
	while(*str)
		putChar(*str++);
}

void kprintf(const char *format, ...)
{
	uint32_t u_32_int;
	char *strPtr, numStr[6];
	va_list args;
	va_start(args, format);
	
	while(*format)
		{
		if(*format == '%')
			{
			switch (*(++format))
				{
				case 's'://string
					strPtr = va_arg(args, char *);
					print(strPtr);
					break;
				case 'd'://unsigned integer
					u_32_int = va_arg(args, uint32_t);
					intToStr(numStr, (int)u_32_int, 10);
					print(numStr);
					break;
				case 'u'://unsigned integer
					u_32_int = va_arg(args, uint32_t);
					uIntToStr(numStr, u_32_int, 10);
					print(numStr);
					break;
				case 'x'://hexadecimal unsigned integer
					u_32_int = va_arg(args, uint32_t);
					uIntToStr(numStr, u_32_int, 16);
					print("0x");
					print(numStr);
					break;
				case '%':
					putChar('%');
					break;
				default://unrecognized
					putChar('%');
					putChar(*format);
					break;
				}
			}
		else
			{
			putChar(*format);
			}
		format++;
		}
	
	va_end(args);
}
