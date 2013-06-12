#include "cpuInfo.h"

extern inline void cpuid(int code, uint32_t *a, uint32_t *d)
{
	ASM("cpuid":"=a"(*a),"=d"(*d):"a"(code):"ecx","ebx");
}