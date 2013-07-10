; loader/longmode.inc
;
; Provides assembly functions to initialize long mode.
;
; Copyright (C) 2013 Lasse Schuirmann. All Rights Reserved.
; Written by Lasse Schuirmann (lasse.schuirmann@gmail.com)
;
; This program is free software: you can redistribute it and/or modify it under
; the terms of the GNU General Public License as published by the Free Software
; Foundation, either version 3 of the License, or (at your option) any later
; version.

; bool longModeSupport()
global longModeSupport
longModeSupport:
	push ebx
	push ecx
	push edx
	
	mov eax, 0x80000001
	cpuid
	; extract the longmode bit
	and edx, CPUID_LM_BIT
	test edx, edx
	jz lmunsupported
		mov eax, 1
		cpuid
		; check if page adress extension is available too
		and edx, CPUID_PAE_BIT
		test edx, edx
		jz lmunsupported
		
		mov eax, 1
		jmp longModeSupportRet
	lmunsupported:
		mov eax, 0
		jmp longModeSupportRet
longModeSupportRet:
	pop edx
	pop ecx
	pop ebx
	ret

; bool activateLongMode()
global activateLongMode
activateLongMode:
	call longModeSupport
	test eax, eax
	jnz lmavail
		; eax is already zero
		ret
lmavail:
	call deactivatePaging
	call enablePAE
	; TODO 64 bit paging
	cli
	hlt
	
	
	
	ret
	