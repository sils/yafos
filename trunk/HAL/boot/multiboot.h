/* multiboot.h
 * 
 * Loads architecture dependend source files for multiboot header.
 *
 * Copyright (C) 2013 Lasse Schuirmann. All Rights Reserved.
 * Written by Lasse Schuirmann (lasse.schuirmann@gmail.com)
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 */

#ifndef _MULTIBOOT_H
#define _MULTIBOOT_H

#ifdef __i386__
#include "x86_multiboot.h"
#else
#error "Unsupported architecture!"
#endif

#endif /* _MULTIBOOT_H */