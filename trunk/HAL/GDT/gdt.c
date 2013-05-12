#include "gdt.h"

static void getSetGate()
{
	return;//TODO
}

#define gdtSetCode() gdtSetGate()//TODO
#define gdtSetData() gdtSetGate()//TODO

#define GDT_ENTRIES 5
void installGdt(void)
{
	getSetGate();
	return;//TODO
}