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
#include "Interrupts/InterruptsDescriptorTable.hpp"
#include "Interrupts/InterruptHandlersGenerator/InterruptHandlersGenerator.hpp"

extern "C"
{
	void kernel_main()
	{
        Terminal::get().initialize();

        InterruptHandlersGenerator interruptHandlersGenerator;
        InterruptDescriptorTable idt;

        PrintUtils::printk("[*] Interrupt table initialized.\n");

        asm volatile("int $3");
        asm volatile (".word 0xFFFF");
        PrintUtils::printk("%d\n", 1/ 0);
		while (1);
	}
}
