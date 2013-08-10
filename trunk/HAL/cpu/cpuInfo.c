#include "cpuInfo.h"

#include <stdlib.h>
#include <print.h>

extern bool evalCpuidSupport();

void assertCpuidSupport()
{
	//we don't need to check again each time
	static bool asserted = false;
	if(asserted)
	{
		return;
	}
	
	if(!evalCpuidSupport())
	{
		fatalErr("CPUID is not supported by your processor!");
	}
	
	asserted = true;
}

void assertLongModeSupport()
{
	static bool asserted = false;
	if(asserted)
	{
		return;
	}
	
	assertCpuidSupport();
	if(!longModeSupport())
	{
		fatalErr("Long mode is not supported by your processor!");
	}
	
	asserted = true;
}