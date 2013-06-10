/* generalInt.h
 * 
 * Provides the general interrupt handler.
 * 
 * Copyright (C) 2013 Lasse Schuirmann. All Rights Reserved.
 * Written by Lasse Schuirmann (lasse.schuirmann@gmail.com)
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 */

#ifndef _GENERAL_INT_H
#define _GENERAL_INT_H

#include <cpu/IDT/idt.h>
#include <stdint.h>
#include <cpu/registers.h>

typedef void (*intHandler)(registers_t*);
void registerIntHandler(uint16_t id, intHandler func);

#include <print.h>
#include <PIC/pic.h>
#include <intHandlers/timerInt.h>

#endif /* _GENERAL_INT_H */
