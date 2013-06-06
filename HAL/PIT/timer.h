/* HAL/PIT/timer.h
 * 
 * TODO description
 * 
 * Copyright (C) 2013 Lasse Schuirmann. All Rights Reserved.
 * Written by Lasse Schuirmann (lasse.schuirmann@gmail.com)
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 */

#ifndef _PIT_TIMER_H
#define _PIT_TIMER_H

#include <stdint.h>

uint8_t initTimer(uint16_t freq);

#include <PIT/pit.h>
#include <sys/io.h>
#include <intHandlers/generalInt.h>
#include <intHandlers/timerInt.h>

#endif /* _PIT_TIMER_H */