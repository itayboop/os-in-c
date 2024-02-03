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

#include "vga_buffer.hpp"
#include "InterruptDescriptorTable.hpp"
#include "InterruptServiceRoutineInitializer.hpp"

extern "C"
{
	void kernel_main()
	{
		terminal_initialize();
		//TOOD: can i just do `InterruptServiceRoutineInitializer();` ?
		const InterruptServiceRoutineInitializer isr_initializer = InterruptServiceRoutineInitializer();
		
	}
}

// TODO: add cpp to each hpp (in it's corresponding tree)
// TODO: add hpp to each asm (in it's corresponding tree)
