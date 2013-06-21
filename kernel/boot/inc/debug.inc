; loader/debug.inc
;
; Provides macros to call debug C functions
;
; Copyright (C) 2013 Lasse Schuirmann. All Rights Reserved.
; Written by Lasse Schuirmann (lasse.schuirmann@gmail.com)
;
; This program is free software: you can redistribute it and/or modify it under
; the terms of the GNU General Public License as published by the Free Software
; Foundation, either version 3 of the License, or (at your option) any later
; version.

extern kprintf

%macro PRINT 2

; store eax
push eax
push %2
push %1

call kprintf

chlp:
cli
hlt
jmp chlp

%endmacro