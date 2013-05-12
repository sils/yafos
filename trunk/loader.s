; init.s
;
; Contains the nessecary instructions to load the C kernel. Therefore it is the
; bridge from an arbitrary multiboot compliant bootloader to the C kernel.
; That includes specificly the following tasks:
; 		build up a stack
; 		TODO read multiboot structure and pass it to the kernel
; 		Call the kernel
; 		Halt the system if the kernel returns

; Declarations
global loader
global hltLoop
extern init

; Definition macros
%define STACKSIZE 0x2000 ; 8kiB Stack

section .multiboot 
; setting up the Multiboot header - see GRUB docs for details
; a multiboot compliant bootloader will read the parameters from here
; TODO check if defines are working here
%define MODULEALIGN  1<<0                   ; align loaded modules on page boundaries
%define MEMINFO      1<<1                   ; provide memory map
MAGIC       equ  0x1BADB002             ; 'magic number' lets bootloader find the header
FLAGS       equ  MODULEALIGN | MEMINFO  ; this is the Multiboot 'flag' field
CHECKSUM    equ -(MAGIC + FLAGS)        ; checksum required

align 4 ; these are 4 bytes in length for meeting multiboot requirements
    dd MAGIC
    dd FLAGS
    dd CHECKSUM
; more information
; http://www.gnu.org/software/grub/manual/multiboot/multiboot.pdf

section .text

loader:
	mov  esp, stack
	; TODO pass multiboot structure to the stack
	; init function is defined in init.c
	call init
	; If the kernel returns halt the system
	jmp hltLoop

hltLoop:
	hlt
	jmp hltLoop

; All the code needed by the C kernel
%include "loader/include.inc"

section .bss
align 4
stackend: resb STACKSIZE
stack: