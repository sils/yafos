/* THE FOLLOWING CODE IS COPIED FROM
http://www.lowlevel.eu/wiki/Teil_8_-_Ein_erstes_Programm
AND WILL BE REPLACED LATER. */

/*  Bei _start soll die Ausfuehrung losgehen */
ENTRY(_start)

OUTPUT_FORMAT(binary)

/*
 * Hier wird festgelegt, in welcher Reihenfolge welche Sektionen in die Binary
 * geschrieben werden sollen
 */
SECTIONS
{
    /* Das Programm wird an 2 MB geladen */
    . = 0x200000;

    .text : {
        *(.text)
    }
    .data ALIGN(4096) : {
        *(.data)
    }
    .rodata ALIGN(4096) : {
        *(.rodata)
    }
    .bss ALIGN(4096) : {
        *(.bss)
    }
}