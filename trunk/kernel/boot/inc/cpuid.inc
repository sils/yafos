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
global evalCpuidSupport
evalCpuidSupport:
	push ebx
	; get flags into eax
	pushfd
	pop eax
	xor eax, 0x200000
	push eax
	popfd
	; if the flag survived, cpuid is supported
	pushfd
	pop ebx
	
	xor ebx, eax
	je cssupported
		mov eax, 0
		pop ebx
		ret
	cssupported:
		mov eax, 1
		pop ebx
		ret

cpuInfoVar: times 16 dd 0

; char *getVendor()
global getVendor
getVendor:
	push ebx
	push ecx
	push edx
	
	xor eax, eax
	cpuid
	
	mov [cpuInfoVar], ebx
	mov [cpuInfoVar+4], edx
	mov [cpuInfoVar+8], ecx
	mov byte [cpuInfoVar+12], 0
	lea eax, [cpuInfoVar]
	
	pop edx
	pop ecx
	pop ebx
	ret

; cpuId_t genCpuId(uint32_t function)
global genCpuId
genCpuId:
	push ebx
	push ecx
	push edx
	
	mov eax, [esp+16]
	
	cpuid
	
	mov [cpuInfoVar   ], eax
	mov [cpuInfoVar+4 ], ebx
	mov [cpuInfoVar+8 ], ecx
	mov [cpuInfoVar+12], edx
	
	lea eax, [cpuInfoVar]
	
	pop edx
	pop ecx
	pop ebx
	ret

; bool longModeSupport()
global longModeSupport
longModeSupport:
	push ebx
	push ecx
	push edx
	
	mov eax, 0x80000001
	cpuid
	; extract the longmode bit
	and edx, 0x20000000
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
