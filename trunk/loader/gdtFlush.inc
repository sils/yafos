; loader/gdtFlush.inc
;
; Provides the function void gdtFlush(void) wich loads the gdt and jumps to the
; kernel code segment.
;
; Copyright (C) 2013 Lasse Schuirmann. All Rights Reserved.
; Written by Lasse Schuirmann (lasse.schuirmann@gmail.com)
;
; This program is free software: you can redistribute it and/or modify it under
; the terms of the GNU General Public License as published by the Free Software
; Foundation, either version 3 of the License, or (at your option) any later
; version.

global gdtFlush
extern tgdtPtr

gdtFlush:
	lgdt [tgdtPtr]
	; Load new data segment offset into segment registers
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	; far jump to code segment (offset 0x08)
	jmp 0x08:flush2
flush2:
	ret