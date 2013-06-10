/* timerInt.h
 * 
 * Provides timer hinterrupt handlers.
 * 
 * Copyright (C) 2013 Lasse Schuirmann. All Rights Reserved.
 * Written by Lasse Schuirmann (lasse.schuirmann@gmail.com)
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 */

#ifndef _TIMERINT_H
#define _TIMERINT_H

#include <cpu/registers.h>

void generalTimerHandler(registers_t *regs);
#define registerTimerHandler(irq)	registerIntHandler((irq), &generalTimerHandler)

#include <print.h>
#include <cpu/IDT/idt.h>
#include <settings.h>
#include <sound/speaker.h>

#endif /* _TIMERINT_H */
