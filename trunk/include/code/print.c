#include <print.h>

//TODO
void printErr()
{
}

void printFatalErr()
{
}

void printDebug()
{
}

// TODO place this where it belongs -> POSIX???
#define charDigit(val)	(val<10?val+'0':val-10+'A')

// TODO move this to a file where it belongs
// and make it posix conform or so.
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
// and make it posix conform or so.
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
	volatile unsigned char *videoram = (unsigned char *)FB_MEM_LOCATION;
	for(i=0;i<(FB_LINES-1)*FB_COLUMNS*2;i++)
		videoram[i]=videoram[i+(FB_COLUMNS * 2)];
	for(; i<2*FB_LINES*FB_COLUMNS;i++)
	{
		if(i % 2)
			videoram[i]=COLCODE(STDFG, STDBG);
		else videoram[i]=BLANK;
	}
}

void clearScreen()
{
	uint16_t i;
	volatile unsigned char *videoram = (unsigned char *)FB_MEM_LOCATION;
	for(i=0;i<25*80*2;i++)
		if(i % 2)
			videoram[i]=COLCODE(STDFG, STDBG);
		else videoram[i]=BLANK;
}

static void setCursor(int pos)
{
	outb(FB_CMD,  FB_HIGH_B);
	outb(FB_DATA, (pos>>8) & 0xFF);
	outb(FB_CMD,  FB_LOW_B);
	outb(FB_DATA, pos & 0xFF);
}

void put(const unsigned char val, const uint8_t color)
{
	static uint8_t x=0, y=0;
	volatile unsigned char *videoram = (unsigned char *)FB_MEM_LOCATION;
	
	//add support for color codes :)
	
	if(val == NEWLN)
	{
		x=0;
		y++;
		if(y>24)//scroll up one line
		{
			scrollUp();
			y--;
		}
		setCursor(GET_POS(x,y));
		return;
	}
	
	if(val == BACKSP)
	{
		if(x>0)
		{
			x--;
			videoram[2*GET_POS(x,y)] = BLANK;
			videoram[2*GET_POS(x,y)+1] = color;
			setCursor(GET_POS(x,y));
			return;
		}
		else
		{
			return;
		}
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
	
	videoram[2*GET_POS(x,y)] = val;
	videoram[2*GET_POS(x,y)+1] = color;
	setCursor(GET_POS(x,y));
	x++;
}

void print(char *str)
{
	while(*str)
		putChar(*str++);//TODO make the color a static global variable
		//wich can be changed through sending standard hex values
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
