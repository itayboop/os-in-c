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

#include "utils.hpp"
#include "idtUtils.hpp"
#include "vga_buffer.hpp"
#include "InterruptDescriptorTable.hpp"

extern "C"
{
	void kernel_main()
	{
		terminal_initialize();

		initialize_idt();
		printf("[*] Interrupt table initialized.\n");

		IdtUtils::register_all_interrupt_handlers();
		printf("[*] Preliminary interrupt handlers set up.\n");

		printf("%d\n", 1 /0);

		printf("did not crush");
	}
}

// TODO: add cpp to each hpp (in it's corresponding tree)
// TODO: add hpp to each asm (in it's corresponding tree)
