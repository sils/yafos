/* HAL/IDT/idt.h
 * 
 * Provides function headers for manupulating the interrupt descriptor table.
 */

#ifndef _IDT_H
#define _IDT_H

#include <stdint.h>

void installIdt(void);

#endif /* _IDT_H */