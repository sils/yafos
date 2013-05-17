/* HAL/intHandlers/keyboardInt.h
 * 
 * Provides the keyboard interrupt handler wich uses the keyboard driver for
 * getting the information.
 * 
 * Copyright (C) 2013 Lasse Schuirmann. All Rights Reserved.
 * Written by Lasse Schuirmann (lasse.schuirmann@gmail.com)
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 */

#ifndef _KEYBOARDINT_H
#define _KEYBOARDINT_H

#include <cpu/registers.h>

void generalKbdHandler(registers_t *regs);

#include <print.h>

#endif /* _KEYBOARDINT_H */