#include "idt.h"

static void idtSetGate(uint8_t index, uint32_t entry, uint16_t selector, uint16_t attr)
{
	idt[index].zero = 0x00;
	idt[index].attr = attr;
	idt[index].selector  = selector;
	idt[index].entryLow	 = 0xFFFF & entry;
	idt[index].entryHigh = (entry>>16) & 0xFFFF;
}

void installIdt(void)
{
	tidtPtr.limit = (sizeof(idtEntry) * IDT_ENTRIES)-1;
	tidtPtr.base  = &idt;
	
	memset((void *)idt, 0, sizeof(idtEntry)*IDT_ENTRIES);
	
	//set gates for all exceptions
	idtSetGate(0 , (uint32_t)isr0 , CALC_SEL(1), I_PRESENT_BIT | I_DPL_BITS(0) | I_INT_GATE_BITS);
	idtSetGate(1 , (uint32_t)isr1 , CALC_SEL(1), I_PRESENT_BIT | I_DPL_BITS(0) | I_INT_GATE_BITS);
	idtSetGate(2 , (uint32_t)isr2 , CALC_SEL(1), I_PRESENT_BIT | I_DPL_BITS(0) | I_INT_GATE_BITS);
	idtSetGate(3 , (uint32_t)isr3 , CALC_SEL(1), I_PRESENT_BIT | I_DPL_BITS(0) | I_INT_GATE_BITS);
	idtSetGate(4 , (uint32_t)isr4 , CALC_SEL(1), I_PRESENT_BIT | I_DPL_BITS(0) | I_INT_GATE_BITS);
	idtSetGate(5 , (uint32_t)isr5 , CALC_SEL(1), I_PRESENT_BIT | I_DPL_BITS(0) | I_INT_GATE_BITS);
	idtSetGate(6 , (uint32_t)isr6 , CALC_SEL(1), I_PRESENT_BIT | I_DPL_BITS(0) | I_INT_GATE_BITS);
	idtSetGate(7 , (uint32_t)isr7 , CALC_SEL(1), I_PRESENT_BIT | I_DPL_BITS(0) | I_INT_GATE_BITS);
	idtSetGate(8 , (uint32_t)isr8 , CALC_SEL(1), I_PRESENT_BIT | I_DPL_BITS(0) | I_INT_GATE_BITS);
	idtSetGate(9 , (uint32_t)isr9 , CALC_SEL(1), I_PRESENT_BIT | I_DPL_BITS(0) | I_INT_GATE_BITS);
	idtSetGate(10, (uint32_t)isr10, CALC_SEL(1), I_PRESENT_BIT | I_DPL_BITS(0) | I_INT_GATE_BITS);
	idtSetGate(11, (uint32_t)isr11, CALC_SEL(1), I_PRESENT_BIT | I_DPL_BITS(0) | I_INT_GATE_BITS);
	idtSetGate(12, (uint32_t)isr12, CALC_SEL(1), I_PRESENT_BIT | I_DPL_BITS(0) | I_INT_GATE_BITS);
	idtSetGate(13, (uint32_t)isr13, CALC_SEL(1), I_PRESENT_BIT | I_DPL_BITS(0) | I_INT_GATE_BITS);
	idtSetGate(14, (uint32_t)isr14, CALC_SEL(1), I_PRESENT_BIT | I_DPL_BITS(0) | I_INT_GATE_BITS);
	idtSetGate(15, (uint32_t)isr15, CALC_SEL(1), I_PRESENT_BIT | I_DPL_BITS(0) | I_INT_GATE_BITS);
	idtSetGate(16, (uint32_t)isr16, CALC_SEL(1), I_PRESENT_BIT | I_DPL_BITS(0) | I_INT_GATE_BITS);
	idtSetGate(17, (uint32_t)isr17, CALC_SEL(1), I_PRESENT_BIT | I_DPL_BITS(0) | I_INT_GATE_BITS);
	idtSetGate(18, (uint32_t)isr18, CALC_SEL(1), I_PRESENT_BIT | I_DPL_BITS(0) | I_INT_GATE_BITS);
	idtSetGate(19, (uint32_t)isr19, CALC_SEL(1), I_PRESENT_BIT | I_DPL_BITS(0) | I_INT_GATE_BITS);
	idtSetGate(20, (uint32_t)isr20, CALC_SEL(1), I_PRESENT_BIT | I_DPL_BITS(0) | I_INT_GATE_BITS);
	idtSetGate(21, (uint32_t)isr21, CALC_SEL(1), I_PRESENT_BIT | I_DPL_BITS(0) | I_INT_GATE_BITS);
	idtSetGate(22, (uint32_t)isr22, CALC_SEL(1), I_PRESENT_BIT | I_DPL_BITS(0) | I_INT_GATE_BITS);
	idtSetGate(23, (uint32_t)isr23, CALC_SEL(1), I_PRESENT_BIT | I_DPL_BITS(0) | I_INT_GATE_BITS);
	idtSetGate(24, (uint32_t)isr24, CALC_SEL(1), I_PRESENT_BIT | I_DPL_BITS(0) | I_INT_GATE_BITS);
	idtSetGate(25, (uint32_t)isr25, CALC_SEL(1), I_PRESENT_BIT | I_DPL_BITS(0) | I_INT_GATE_BITS);
	idtSetGate(26, (uint32_t)isr26, CALC_SEL(1), I_PRESENT_BIT | I_DPL_BITS(0) | I_INT_GATE_BITS);
	idtSetGate(27, (uint32_t)isr27, CALC_SEL(1), I_PRESENT_BIT | I_DPL_BITS(0) | I_INT_GATE_BITS);
	idtSetGate(28, (uint32_t)isr28, CALC_SEL(1), I_PRESENT_BIT | I_DPL_BITS(0) | I_INT_GATE_BITS);
	idtSetGate(29, (uint32_t)isr29, CALC_SEL(1), I_PRESENT_BIT | I_DPL_BITS(0) | I_INT_GATE_BITS);
	idtSetGate(30, (uint32_t)isr30, CALC_SEL(1), I_PRESENT_BIT | I_DPL_BITS(0) | I_INT_GATE_BITS);
	idtSetGate(31, (uint32_t)isr31, CALC_SEL(1), I_PRESENT_BIT | I_DPL_BITS(0) | I_INT_GATE_BITS);
	
	//set gates for all hardware IRQs (with one master and slave its 16 IRQs)
	idtSetGate(32, (uint32_t)irq0 , CALC_SEL(1), I_PRESENT_BIT | I_DPL_BITS(0) | I_INT_GATE_BITS);
	idtSetGate(33, (uint32_t)irq1 , CALC_SEL(1), I_PRESENT_BIT | I_DPL_BITS(0) | I_INT_GATE_BITS);
	idtSetGate(34, (uint32_t)irq2 , CALC_SEL(1), I_PRESENT_BIT | I_DPL_BITS(0) | I_INT_GATE_BITS);
	idtSetGate(35, (uint32_t)irq3 , CALC_SEL(1), I_PRESENT_BIT | I_DPL_BITS(0) | I_INT_GATE_BITS);
	idtSetGate(36, (uint32_t)irq4 , CALC_SEL(1), I_PRESENT_BIT | I_DPL_BITS(0) | I_INT_GATE_BITS);
	idtSetGate(37, (uint32_t)irq5 , CALC_SEL(1), I_PRESENT_BIT | I_DPL_BITS(0) | I_INT_GATE_BITS);
	idtSetGate(38, (uint32_t)irq6 , CALC_SEL(1), I_PRESENT_BIT | I_DPL_BITS(0) | I_INT_GATE_BITS);
	idtSetGate(39, (uint32_t)irq7 , CALC_SEL(1), I_PRESENT_BIT | I_DPL_BITS(0) | I_INT_GATE_BITS);
	idtSetGate(40, (uint32_t)irq8 , CALC_SEL(1), I_PRESENT_BIT | I_DPL_BITS(0) | I_INT_GATE_BITS);
	idtSetGate(41, (uint32_t)irq9 , CALC_SEL(1), I_PRESENT_BIT | I_DPL_BITS(0) | I_INT_GATE_BITS);
	idtSetGate(42, (uint32_t)irq10, CALC_SEL(1), I_PRESENT_BIT | I_DPL_BITS(0) | I_INT_GATE_BITS);
	idtSetGate(43, (uint32_t)irq11, CALC_SEL(1), I_PRESENT_BIT | I_DPL_BITS(0) | I_INT_GATE_BITS);
	idtSetGate(44, (uint32_t)irq12, CALC_SEL(1), I_PRESENT_BIT | I_DPL_BITS(0) | I_INT_GATE_BITS);
	idtSetGate(45, (uint32_t)irq13, CALC_SEL(1), I_PRESENT_BIT | I_DPL_BITS(0) | I_INT_GATE_BITS);
	idtSetGate(46, (uint32_t)irq14, CALC_SEL(1), I_PRESENT_BIT | I_DPL_BITS(0) | I_INT_GATE_BITS);
	idtSetGate(47, (uint32_t)irq15, CALC_SEL(1), I_PRESENT_BIT | I_DPL_BITS(0) | I_INT_GATE_BITS);
	
	//flush :)
	cli();
	remapIrqs();
	lidt(tidtPtr);
}