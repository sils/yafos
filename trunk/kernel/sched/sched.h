/* sched.h
 * 
 * Provides prototypes for the scheduler.
 *
 * Copyright (C) 2013 Lasse Schuirmann. All Rights Reserved.
 * Written by Lasse Schuirmann (lasse.schuirmann@gmail.com)
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 */

#ifndef _SCHED_H
#define _SCHED_H

#include <cpu/registers.h>

void initScheduler(const void *kernelEnt, const void *virtEnt, const void end);
//physEnd is to be the physical adress after the last
//TODO
void addTask(const void *physEnt, const void *virtEnt, const void *physEnd);
//TODO maybe return an errno
void schedule(registers_t *regs);

#endif /* _SCHED_H */
