; loader/intHandler.inc
;
; Provides interrupt handler that call kernel procedures.
;
; Copyright?
;
; This program is free software: you can redistribute it and/or modify it under
; the terms of the GNU General Public License as published by the Free Software
; Foundation, either version 3 of the License, or (at your option) any later
; version.

%macro ISR_NOERR 1
global isr%1
isr%1:
	cli
	; no error code
	push byte 0
	; push interrupt number
	push byte %1
	jmp commonInt
%endmacro

%macro ISR_ERR 1
global isr%1
isr%1:
	cli
	; error code is pushed automatically, push interrupt number
	push byte %1

	jmp commonInt
%endmacro

%macro IRQ 2
global irq%1
irq%1:
	cli
	push byte 0
	push byte %2
	jmp commonInt
%endmacro

ISR_NOERR 0
ISR_NOERR 1
ISR_NOERR 2
ISR_NOERR 3
ISR_NOERR 4
ISR_NOERR 5
ISR_NOERR 6
ISR_NOERR 7
ISR_ERR 8
ISR_NOERR 9
ISR_ERR 10
ISR_ERR 11
ISR_ERR 12
ISR_ERR 13
ISR_ERR 14
ISR_NOERR 15
ISR_NOERR 16
ISR_NOERR 17
ISR_NOERR 18
ISR_NOERR 19
ISR_NOERR 20
ISR_NOERR 21
ISR_NOERR 22
ISR_NOERR 23
ISR_NOERR 24
ISR_NOERR 25
ISR_NOERR 26
ISR_NOERR 27
ISR_NOERR 28
ISR_NOERR 29
ISR_NOERR 30
ISR_NOERR 31
IRQ   0,    32
IRQ   1,    33
IRQ   2,    34
IRQ   3,    35
IRQ   4,    36
IRQ   5,    37
IRQ   6,    38
IRQ   7,    39
IRQ   8,    40
IRQ   9,    41
IRQ  10,    42
IRQ  11,    43
IRQ  12,    44
IRQ  13,    45
IRQ  14,    46
IRQ  15,    47

;now the nasty things:
; TODO support 64 bit registers
extern generalIntHandler
commonInt:
	; push everything compliant to the registers_t structure of the kernel
    pusha ; pushes edi,esi,ebp,esp,ebx,edx,ecx,eax

    ; save data segment
    mov ax, ds
    push eax

    ; get to kernel segment
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ; push pointer to stack
    push esp
    call generalIntHandler; Call into our C code.
    ; no need to pop esp from stack
    add esp, 4

    ;return to original segment
    pop ebx
    mov ds, bx
    mov es, bx
    mov fs, bx
    mov gs, bx
    mov ss, bx

    popa
    add esp, 8; count stack up over the pushed error code and int no
    iret ; TODO maybe macro -> use iretq while in 64 bit mode