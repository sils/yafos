/* modules.h
 * 
 * Provides functions for loading and unloading modules from and to kernel.
 *
 * Copyright (C) 2013 Lasse Schuirmann. All Rights Reserved.
 * Written by Lasse Schuirmann (lasse.schuirmann@gmail.com)
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 */

#ifndef _MODULES_H
#define _MODULES_H

#include <errno.h>

//TODO will load a module and start it as a task
err_t loadModule(const void *startAddr, const void *endAddr);

#endif /* _MODULES_H */
