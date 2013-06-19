#include "multiboot.h"

#if ARCH == 32

//nothing there yet ;)

#elif ARCH == 64
error "[ERROR] Unimplemented!"
#else
#error "UNKNOWN ARCHITECTURE"
#endif /* ARCH == 32 */