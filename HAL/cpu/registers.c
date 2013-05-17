#include "registers.h"

void regDump(registers_t regs)
{
	kprintf("Register dump:\n");
	kprintf("   ds : %x\n",regs.ds);
	kprintf("   edi: %x\n",regs.edi);
	kprintf("   esi: %x\n",regs.esi);
	kprintf("   ebp: %x\n",regs.ebp);
	kprintf("   esp: %x\n",regs.esp);
	kprintf("   ebx: %x\n",regs.ebx);
	kprintf("   edx: %x\n",regs.edx);
	kprintf("   ecx: %x\n",regs.ecx);
	kprintf("   eax: %x\n",regs.eax);
	kprintf("   eip: %x\n",regs.eip);
	kprintf("   cs : %x\n",regs.cs);
	kprintf("   efl: %x\n",regs.eflags);
	kprintf("   ues: %x\n",regs.useresp);
	kprintf("   ss : %x\n",regs.ss);
	
	kprintf("   int_no: %x\n",regs.int_no);
	kprintf("   err_code: %x\n",regs.err_code);
}