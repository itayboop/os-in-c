// Check if the compiler thinks you are targeting the wrong operating system.
#ifdef __linux__
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

// Check if compiled with the right compiler
#ifndef __x86_64__
#error "This OS needs to be compiled with a x86_64-elf compiler"
#endif

#include "VgaBuffer.hpp"
#include "Arch/InterruptDescriptorTable.hpp"
#include "Utils/Functions/PrintUtils.hpp"
#include "Arch/InterruptServiceRoutine/InterruptServiceRoutineInitializer.hpp"

extern "C"
{
	void kernel_main()
	{
		terminal_initialize();

		PrintUtils::printk("[*] Initializing ISR entries...\n");
		InterruptServiceRoutineInitializer();
		PrintUtils::printk("[*] Initialized ISR entries\n\n");

		PrintUtils::printk("[*] Initializing IDT...\n");
		InterruptDescriptorTable idt = InterruptDescriptorTable();
		PrintUtils::printk("[*] Initialized IDT\n");

//		const IdtEntry first_entry = idt.getEntries()[0];
//		uint64_t offset = (static_cast<uint64_t>(first_entry.isr_high) << 32) | (static_cast<uint16_t>(first_entry.isr_mid) << 16) | first_entry.isr_low;
//		auto funcPtr = reinterpret_cast<void(*)()>(offset);
//		PrintUtils::printk("about to call divide by zero\n");
//		funcPtr();
		// PrintUtils::printk("%x %x %x", first_entry.isr_low, first_entry.isr_mid, first_entry.isr_high);
//		 PrintUtils::printk("%d\n", 1 / 0);
		while (1);

	}
}

// TODO: add hpp to each asm (in it's corresponding tree)
// TODO: change "initializer" to scoped (::initialize())
