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

#include "interrupts.h"
#include "vga_buffer.h"
#include "utils.h"
#include "idt.h"

void kernel_main(void)
{
	terminal_initialize();

	initialize_idt();
	printf("[*] Interrupt table initialized.\n");

	register_all_interrupt_handlers();
	printf("[*] Preliminary interrupt handlers set up.\n");

	asm("int3");

	printf("did not crush");
}

