/* linker.ld
 *
 * Linker script wich guarantees page aligned sections and provides kernelStart
 * and kernelEnd symbols so that the memory manager may determine where NOT to
 * write things to.
 * 
 * Copyright (C) 2013 Lasse Schuirmann. All Rights Reserved.
 * Written by Lasse Schuirmann (lasse.schuirmann@gmail.com)
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 */

/* let's dive into the kernel land - with the NASM label 'loader' */
ENTRY (loader)

SECTIONS
{
	. = 0x100000;
    
    kernelStart = .;

    .text ALIGN (0x1000) :
    {
    	*(.multiboot)
        *(.text)
    }

    .rodata ALIGN (0x1000) :
    {
        *(.rodata*)
    }

    .data ALIGN (0x1000) :
    {
        *(.data)
    }

    .bss :
    {
        *(.bss)
    }
    
    . = ALIGN(0x1000);
    kernelEnd = .;
}