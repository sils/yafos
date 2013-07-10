#include "cpuInfo.h"

#include <stdlib.h>
#include <stdMacro.h>

extern bool evalCpuidSupport();

void assertCpuidSupport()
{
	if(!evalCpuidSupport())
	{
		fatalErr("CPUID is not supported by your processor!");
	}
}