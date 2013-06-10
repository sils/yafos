/* pit.h
 * 
 * Making life easier when arguing with the PIT.
 * See http://wiki.osdev.org/PIT for more information about modes and so on.
 * 
 * Copyright (C) 2013 Lasse Schuirmann. All Rights Reserved.
 * Written by Lasse Schuirmann (lasse.schuirmann@gmail.com)
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 */

#ifndef _PIT_PIT_H
#define _PIT_PIT_H

#define PIT_COMMAND(cmd)	outb(PIT_CMD, (cmd))
#define PIT_WRITE(ch, val);	outb(PIT_DATA(ch), (val) & 0xFF);\
							outb(PIT_DATA(ch), (val) >> 8);

//
// All the nice constants for a 8253/8254 chip
//

//ports
#define PIT_DATA(chan)	0x40 | (chan)
//only for write access
#define PIT_CMD			0x43

//possibilities for command register:
#define PIT_BCD_MODE	1 //four digit bcd. If unset: binary
#define PIT_MODE(mode)	(mode)	<< 1
#define PIT_ACCESS(am)	(am)	<< 4
#define PIT_CHANNEL(ch)	(ch)	<< 6

//waits for hardware to trigger countdown
#define PIT_M_HW_WAIT	PIT_MODE(5)

//access first the low byte, then the high byte
#define PIT_ACCESS_ALL	PIT_ACCESS(3)

//general
#define PIT_MINFREQ		18
#define PIT_MAXFREQ		65535
//almost accurate. There is about 1/3Hz too much
#define PIT_FREQ		1193182

#endif /* _PIT_PIT_H */
