#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "vga_buffer.h"

/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

void kernel_main(void) {
    terminal_initialize();

    // terminal_write_int(12345);
    terminal_write_int(-12345);

    while(1) {}
}
