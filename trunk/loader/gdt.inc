; include/gdt.inc
;
; Contains functions to load the global descriptor table.
;
; Copyright (C) 2013 Lasse Schuirmann. All Rights Reserved.
; Written by Lasse Schuirmann (lasse.schuirmann@gmail.com)
;
; This program is free software: you can redistribute it and/or modify it under
; the terms of the GNU General Public License as published by the Free Software
; Foundation, either version 3 of the License, or (at your option) any later
; version.

global loadGdt
extern globalGdtPtr

loadGdt:
	cli ; just to be sure
	lgdt [globalGdtPtr]
	ret