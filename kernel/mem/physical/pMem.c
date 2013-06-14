#include "pMem.h"

#if ARCH == 32
//static uint32_t bitmap[]//TODO find out, how large the ram is
#else
#error "64-bit mode is not supported by physical memory manager YET."
#endif