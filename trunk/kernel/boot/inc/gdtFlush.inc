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

; void jumpToSegment(uint8_t dataSegment, uint8_t codeSegment)
;
; used registers:
;	eax (may be changed)
global jumpToSegment
jumpToSegment:
	; do not use return address
	add esp, 0x4
	; pop data segment parameter
	pop eax
	
	; set segment adresses
	mov ds, eax
	mov es, eax
	mov fs, eax
	mov gs, eax
	mov ss, eax
	
	; TODO use code segment parameter
	;pop eax
	jmp 0x8:nxt
nxt:
	; reset esp properly; two parameters plus return address
	sub esp, 0x8
	ret
