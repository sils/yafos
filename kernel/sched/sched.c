/* sched.c
 * 
 * Provides the scheduler and some functions for task initializing.
 *
 * Copyright (C) 2013 Lasse Schuirmann. All Rights Reserved.
 * Written by Lasse Schuirmann (lasse.schuirmann@gmail.com)
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 */
/*
#include <stdMacro.h>
#include <stdint.h>
#include <cpu/paging/paging.h>
#include <mem/physical/pMem.h>
#include <settings.h>
#include <cpu/registers.h>

STRUCT
{
	uint16_t id;
	registers_t regs;
	void *pageDir;
} PACKED task_t;

static uint16_t lastId = 0;
static uintptr_t kernEnt, kernVEnt, kernEnd, kernelPDir;

//TODO task death

void initScheduler(const void *kernelEnt, const void *virtEnt, const void *end)
{
	kernEnt=(uintptr_t)kernelEnt;
	kernVEnt=(uintptr_t)virtEnt;
	kernEnd=(uintptr_t)end;
	
	//TODO add kernel task
}

#define STACKADDR	0x100000
void addTask(const void *physEnt, const void *virtEnt, const void *physEnd)
{
	void	*stack;
	void	*pDir;//TODO change this type pageDirEntry or so ;)
	task_t	*task;
	
	//for starters, give te task just 1 page space for the stack and task struct
	//TODO make it extendable
	stack = pMemAlloc(1);
	kprintf("should be 1: %u\n",(PAGE_SIZE-1+sizeof(task_t))/PAGE_SIZE);
	//compiler rounds DOWN, so add (PAGE_SIZE-1)
	task = pMemAlloc((PAGE_SIZE-1+sizeof(task_t))/PAGE_SIZE);
	pDir = pMemAlloc((1024*sizeof(uint32_t))/PAGE_SIZE);
	
	//TODO find a way to do this in a more direct way ;) (no tmp)
	task_t tmp =
	{
		.id = lastId++,
		.regs =
		{
			.edi = 0,
			.esi = 0,
			.ebp = 0,
			//FIXME this may lead to failure
			//it grows upwards!
			.esp = (uintptr_t)STACKADDR + PAGE_SIZE,
			.ebx = 0,
			.edx = 0,
			.ecx = 0,
			.eax = 0,
			
			.eip = (uintptr_t)virtEnt,
			//TODO set segment dynamically
			//maybe make a macro? STD_USER_CS, STD_KERNEL_CS, ...
			.cs  = 0x08,
			//TODO make some macros for these flags
			.eflags = 0x202,
			//rest unused FOR NOW
		},
		.pageDir = pDir
	};
	*task = tmp;
	
	//setting up paging
	//go to kernel page directory
	setPageDir((void*)kernelPDir);
	//TODO map task -> we need a virtual memory manager
	//mapPage((uintptr_t)task, TODO)
	
	//TODO do something about the privilige level!
	//use the new page directory
	setPageDir(pDir);
	//map the kernel to every user process
	mapRegion(kernEnt, kernVEnt, kernEnd);
	//map the stack
	mapPage((uintptr_t)stack, STACKADDR);
	//map code
	mapRegion((uintptr_t)physEnt, (uintptr_t)virtEnt, (uintptr_t)physEnd);
	//map videoram - for now, later this will be forbidden and a syscall will
	//be used - TODO
	mapPage(0xB8000, 0xB8000);
	
	//TODO place it at the end of the qeue
	//TODO: create the qeue ;)
}*/