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

%define CPUID_PAE_BIT	0x00000040
%define CPUID_FLAG_BIT	0x00200000
%define CPUID_LM_BIT	0x20000000

; bool evalCpuidSupport()
global evalCpuidSupport
evalCpuidSupport:
	push ebx
	; get flags into eax
	pushfd
	pop eax
	xor eax, CPUID_FLAG_BIT
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
