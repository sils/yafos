#include "cpuInfo.h"

#include <stdlib.h>

extern bool evalCpuidSupport();

void assertCpuidSupport()
{
	if(!evalCpuidSupport())
	{
		fatalErr("CPUID is not supported by your processor!");
	}
}