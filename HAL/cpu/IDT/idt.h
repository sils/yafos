/* idt.h
 * 
 * Provides function headers for manipulating the interrupt descriptor table.
 * 
 * Copyright (C) 2013 Lasse Schuirmann. All Rights Reserved.
 * Written by Lasse Schuirmann (lasse.schuirmann@gmail.com)
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 */

#ifndef _IDT_H
#define _IDT_H

#include <stdint.h>
#include <stdMacro.h>

STRUCT
{
	uint16_t entryLow;
	uint16_t selector;
	uint8_t  zero;
	uint8_t  attr;
	uint16_t entryHigh;
} PACKED idtEntry;

STRUCT
{
	uint16_t  limit;
	void     *base;
} PACKED idtPtr;

#define IDT_ENTRIES 48
void installIdt(void);

// interrupt handler routines
extern void isr0 ();
extern void isr1 ();
extern void isr2 ();
extern void isr3 ();
extern void isr4 ();
extern void isr5 ();
extern void isr6 ();
extern void isr7 ();
extern void isr8 ();
extern void isr9 ();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

extern void irq0 ();
extern void irq1 ();
extern void irq2 ();
extern void irq3 ();
extern void irq4 ();
extern void irq5 ();
extern void irq6 ();
extern void irq7 ();
extern void irq8 ();
extern void irq9 ();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

#define IRQ0 32
#define IRQ1 33
#define IRQ2 34
#define IRQ3 35
#define IRQ4 36
#define IRQ5 37
#define IRQ6 38
#define IRQ7 39
#define IRQ8 40
#define IRQ9 41
#define IRQ10 42
#define IRQ11 43
#define IRQ12 44
#define IRQ13 45
#define IRQ14 46
#define IRQ15 47

#define I_PRESENT	1<<7
#define I_DPL(dpl)	((dpl)<<5)
#define I_STORAGE	1<<4
#define I_TASK_GATE	0x5//TODO find out about this gate bits EXACTLY
#define I_TRAP_GATE	0xF
#define I_INT_GATE	0xE

#define CALC_SEL(param) (param)*8

#include <sys/io.h>
#include <string.h>
#include <PIC/pic.h>

#endif /* _IDT_H */
