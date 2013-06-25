/* modules.c
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

#include "modules.h"

#include <settings.h>
#include <cpu/paging/paging.h>
#include <stdMacro.h>

err_t loadModule(const void *startAddr, const void *endAddr)
{
	uintptr_t tmp;
	//this maps the module in the kernel space
	/* TODO map it to an own page directory and set the first PD entries to the
	 * kernel page tables. (Oh this is great I'm just that happy) */
	for(tmp = (uintptr_t)startAddr; tmp<(uintptr_t)endAddr; tmp += PAGE_SIZE)
	{
		//TODO don't just ASSUME that the module wants to lie at 2MB
		if( !verify(mapPage((uintptr_t)startAddr,
			((uintptr_t)startAddr - tmp) + 2*MB )) )
		{
			return -ERR_IN_SUBFUNC;
		}
	}
	//TODO create task
	return -NOT_IMPLEMENTED;
}
