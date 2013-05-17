#include "io.h"

//definition has to be extern inline to be visible for other files since inline
//in gcc C99 standard contains an implicit static if not mentioned else
extern inline void outb (uint8_t value, uint16_t port)
{
	__asm__ __volatile__ ("outb %b0,%w1": :"a" (value), "Nd" (port));
}