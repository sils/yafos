/* HAL/PIT/timer.h
 * 
 * Provides functions to initialize and use timers hardware independent!
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

uint8_t	initChannel(uint16_t freq, uint8_t channel, uint8_t mode);
#define initStdTimer(f)		initChannel((f), 0, 2)
#define initSpeakerTimer(f)	initChannel((f), 2, 3)//use square wave generator

#include <PIT/pit.h>
#include <sys/io.h>
#include <intHandlers/generalInt.h>
#include <intHandlers/timerInt.h>

#endif /* _PIT_TIMER_H */