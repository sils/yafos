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

%define PAE_ENABLE_BIT	0x00000020
%define PAGING_BIT		0x80000000

; uint32_t activatePaging(void *pageDirAddr)
global activatePaging
activatePaging:
	; jump over return address
	add esp, 4
	; set page directory address (first parameter)
	pop eax
	
	mov cr3, eax
	
	; activate paging
	mov eax, cr0
	or  eax, PAGING_BIT
	mov cr0, eax
	
	; set stack pointer properly
	sub esp, 8
	ret

; void enablePAE()
global enablePAE
enablePAE:
	mov eax, cr4
	or eax, PAE_ENABLE_BIT
	mov cr4, eax
	ret

; void deactivatePaging()
global deactivatePaging
deactivatePaging:
	mov eax, cr0
	and eax, 0x7FFFFFFF
	mov cr0, eax
	
	ret