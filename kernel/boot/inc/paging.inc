; loader/paging.inc
;
; Provides assembly functions to initialize paging.
;
; Copyright (C) 2013 Lasse Schuirmann. All Rights Reserved.
; Written by Lasse Schuirmann (lasse.schuirmann@gmail.com)
;
; This program is free software: you can redistribute it and/or modify it under
; the terms of the GNU General Public License as published by the Free Software
; Foundation, either version 3 of the License, or (at your option) any later
; version.

; uint32_t activatePaging(void *pageDirAddr)
;
; used registers:
;	eax (may be changed)
;
; returns:
;	eax, status of cr0
global activatePaging
activatePaging:
	; jump over return address
	add esp, 4
	; set page directory address (first parameter)
	pop eax
	
	mov cr3, eax
	
	; activate paging
	mov eax, cr0
	or  eax, 0x80000000
	mov cr0, eax
	
	; set stack pointer properly
	sub esp, 8
	ret

msg db "[ASM] %x",0x0a,0