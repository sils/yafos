; loader/include.inc
;
; Includes all nessecary assembler code.
;
; Copyright (C) 2013 Lasse Schuirmann. All Rights Reserved.
; Written by Lasse Schuirmann (lasse.schuirmann@gmail.com)
;
; This program is free software: you can redistribute it and/or modify it under
; the terms of the GNU General Public License as published by the Free Software
; Foundation, either version 3 of the License, or (at your option) any later
; version.

%include "kernel/boot/inc/debug.inc"
%include "kernel/boot/inc/intHandler.inc"
%include "kernel/boot/inc/gdtFlush.inc"
%include "kernel/boot/inc/paging.inc"
%include "kernel/boot/inc/cpuid.inc"
