/* Check if the compiler thinks you are targeting the wrong operating system. */
#ifdef __linux__
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

/* Check if compiled with the right compiler*/
#ifndef __x86_64__
#error "This tutorial needs to be compiled with a x86_64-elf compiler"
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "interrupts.hpp"
#include "vga_buffer.hpp"
#include "utils.hpp"
#include "idt.hpp"

extern "C"
{
    void kernel_main(void)
    {
        terminal_initialize();

        initialize_idt();
        printf("[*] Interrupt table initialized.\n");

        register_all_interrupt_handlers();
        printf("[*] Preliminary interrupt handlers set up.\n");

        printf("%d\n", 1 / 0);

        // printf("%d hello, another string is: %s, and then another char is: %c and this is try: %a here is another try: %s", 5123, "string string", 'c', "a try");
        // printf("%d", 1 / 0);

        while (1) {}
    }
}
