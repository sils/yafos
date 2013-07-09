; loader/cpuid.inc
;
; Provides functions to access information about the cpu.
;
; Copyright (C) 2013 Lasse Schuirmann. All Rights Reserved.
; Written by Lasse Schuirmann (lasse.schuirmann@gmail.com)
;
; This program is free software: you can redistribute it and/or modify it under
; the terms of the GNU General Public License as published by the Free Software
; Foundation, either version 3 of the License, or (at your option) any later
; version.

; bool evalCpuidSupport()
;
; used registers:
;	eax (may be changed)
;	ebx (will be restored)
global evalCpuidSupport
evalCpuidSupport:
	push ebx
	
	; get flags into eax
	pushfd
	pop eax
	xor eax, 0x200000 ; change ID flag
	
	; load it into eflags
	push eax
	popfd
	; lets see if the flag survived
	pushfd
	pop ebx
	
	xor ebx, eax
	je supported
		mov eax, 0
		
		pop ebx
		ret
	supported:
		mov eax, 1
		
		pop ebx
		ret