// Check if the compiler thinks you are targeting the wrong operating system.
#ifdef __linux__
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

// Check if compiled with the right compiler
#ifndef __x86_64__
#error "This OS needs to be compiled with a x86_64-elf compiler"
#endif

#include "MemoryAllocator.hpp"
#include "OsDefinitions/MemoryOperators.hpp"
#include "Terminal.hpp"
#include "Boot/multiboot.hpp"

#include "Utils/Functions/PrintUtils.hpp"
#include "Utils/Functions/MemoryUtils.hpp"

#include "arch/Interrupts/CpuException.hpp"
#include "arch/Interrupts/APIC.hpp"
#include "arch/Interrupts/InterruptsDescriptorTable.hpp"
#include "arch/Interrupts/InterruptHandlersGenerator/InterruptHandlersGenerator.hpp"

extern "C"
{
void kernel_main(uint32_t magic, uintptr_t addr)
{
    Terminal::get().initialize();

    Multiboot multiboot = Multiboot(magic, addr);
    MemoryRegion heap = multiboot.find_usable_region();

    MemoryAllocator::get().init(reinterpret_cast<void *>(heap.base), heap.length);

    InterruptHandlersGenerator interruptHandlersGenerator;
    InterruptDescriptorTable idt;
    CpuExceptions cpuExceptions;
    cpuExceptions.register_handlers(idt);
    PrintUtils::printk("[*] Interrupt table initialized.\n");

//        ApicInterrupts apic;
//        apic.register_handlers(idt);

    asm volatile("int $3");
    asm volatile (".word 0xFFFF");
    PrintUtils::printk("%d\n", 1 / 0);
    while (1);
}
}
