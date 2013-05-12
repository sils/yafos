/* linker.ld
 *
 * 
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