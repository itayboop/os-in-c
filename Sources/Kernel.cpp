// Check if the compiler thinks you are targeting the wrong operating system.
#ifdef __linux__
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

// Check if compiled with the right compiler
#ifndef __x86_64__
#error "This OS needs to be compiled with a x86_64-elf compiler"
#endif

#include "Terminal.hpp"
#include "Boot/multiboot.hpp"
#include "memory.hpp"
#include "Utils/Functions/PrintUtils.hpp"
#include "Utils/Functions/MemoryUtils.hpp"
#include "Interrupts/InterruptsDescriptorTable.hpp"
#include "Interrupts/InterruptHandlersGenerator/InterruptHandlersGenerator.hpp"

extern "C"
{
    void kernel_main(uint32_t magic, uintptr_t addr)
	{
        Terminal::get().initialize();

        Multiboot multiboot = Multiboot(magic, addr);
        MemoryRegion usable_memory_region = multiboot.find_usable_region();
        PrintUtils::printk("[*] Usable memory region found at %p, size: %d bytes\n", (void*)usable_memory_region.base, usable_memory_region.length);

        init_heap((void*)usable_memory_region.base, usable_memory_region.length);

        char *b = (char *)malloc(128);
        MemoryUtils::memset(b, 51, 63);
        b[63] = '\0';
        PrintUtils::printk("Allocated string at %p: %s\n", b, b);

        InterruptHandlersGenerator interruptHandlersGenerator;
        InterruptDescriptorTable idt;

        PrintUtils::printk("[*] Interrupt table initialized.\n");

        asm volatile("int $3");
        asm volatile (".word 0xFFFF");
        PrintUtils::printk("%d\n", 1 / 0);
		while (1);
	}
}
