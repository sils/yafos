/* speaker.h
 * 
 * Library to get sound of the speaker via channel 2 of the PIT.
 * 
 * Copyright (C) 2013 Lasse Schuirmann. All Rights Reserved.
 * Written by Lasse Schuirmann (lasse.schuirmann@gmail.com)
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 */

#ifndef _SPEAKER_H
#define _SPEAKER_H

#include <stdint.h>

void beepOn(uint32_t frequency);
void beepOff();
//TODO wait function without polling
//void beep(uint32_t frequency, );

#include <PIT/timer.h>
#include <PIT/pit.h>
#include <sys/io.h>

#endif /* _SPEAKER_H */
