#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "vga_buffer.h"

// check if targeting wrong operating system.
#if defined(__linux__)
#error "You are not using a cross compiler, you'll run into troble"
#endif

#if !defined(__i386__)
#error "This works only with an ix86-elf compiler"
#endif

size_t strlen(const char* str) {
    size_t string_length = 0;

    while(str[string_length]) {
        string_length++;
    }

    return string_length;
}

void kernel_main(void) {
    terminal_initialize();

    terminal_write_string("Hello, kernel World!\n");
    terminal_write_string("newline!\n");

    while(1) {}
}
