/* Check if the compiler thinks you are targeting the wrong operating system. */
#ifdef __linux__
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

/* Check if compiled with the right compiler*/
#ifndef __x86_64__
#error "This OS needs to be compiled with a x86_64-elf compiler"
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "VgaBuffer.hpp"
#include "Arch/InterruptDescriptorTable.hpp"
#include "Utils/Functions/PrintUtils.hpp"
#include "Arch/InterruptServiceRoutine/InterruptServiceRoutineInitializer.hpp"

extern "C"
{
	void kernel_main()
	{
		terminal_initialize();
		//TOOD: can i just do `InterruptServiceRoutineInitializer();` ?
		InterruptServiceRoutineInitializer();
		InterruptDescriptorTable();
		PrintUtils::printk("hello");
	}
}

// TODO: add hpp to each asm (in it's corresponding tree)
