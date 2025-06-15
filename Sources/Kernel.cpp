// Check if the compiler thinks you are targeting the wrong operating system.
#ifdef __linux__
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

// Check if compiled with the right compiler
#ifndef __x86_64__
#error "This OS needs to be compiled with a x86_64-elf compiler"
#endif

#include "VgaBuffer.hpp"
#include "Utils/Functions/PrintUtils.hpp"
#include "../Headers/Interrupts/idt.hpp"
#include "../Headers/Interrupts/interrupts.hpp"

extern "C"
{
	void kernel_main()
	{
		terminal_initialize();
        IDT idt = IDT();
        idt.initialize_idt();
        PrintUtils::printk("[*] Interrupt table initialized.\n");

        register_all_interrupt_handlers(&idt);
        PrintUtils::printk("[*] Preliminary interrupt handlers set up.\n");

        PrintUtils::printk("%d\n", 1/ 0);
		while (1);
	}
}

// TODO: add hpp to each asm (in it's corresponding tree)
