#include "cpuInfo.h"

#include <stdlib.h>
#include <print.h>

extern bool evalCpuidSupport();

void assertCpuidSupport()
{
	if(!evalCpuidSupport())
	{
		fatalErr("CPUID is not supported by your processor!");
	}
}

void assertLongModeSupport()
{
	if(!longModeSupport())
	{
		fatalErr("Long mode is not supported by your processor!");
	}
}