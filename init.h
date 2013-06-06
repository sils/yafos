/* init.c
 * 
 * Initializes the kernel properly. That includes specificly:
 * 		Set up a global descriptor table
 * 		Set up a interrupt descriptor table
 * 		Set up a timer for time measurement
* 		TODO Get the speaker running and play a welcome-tone ;)
 * 		TODO Set up memory management
 * 		TODO Set up a dispatcher and scheduler
 *
 * Copyright (C) 2013 Lasse Schuirmann. All Rights Reserved.
 * Written by Lasse Schuirmann (lasse.schuirmann@gmail.com)
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 */

#ifndef _INIT_H
#define _INIT_H

void init();

//For reading information passed from bootloader
#include <boot/boot.h>
//For printing out text to video memory
#include <print.h>
//Setting up a global descriptor table
#include <GDT/gdt.h>
//Setting up an interrupt descriptor table
#include <IDT/idt.h>
//For initializing the timer
#include <PIT/timer.h>

//just temporarily
#include <intHandlers/keyboardInt.h>

#endif /* _INIT_H */
