#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "vga_buffer.hpp"
#include "utils.hpp"

/* Check if the compiler thinks you are targeting the wrong operating system. */
#ifdef __linux__
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

/* Check if compiled with the right compiler*/
#ifndef __x86_64__
#error "This tutorial needs to be compiled with a x86_64-elf compiler"
#endif

extern "C" {
    void kernel_main(void) {
        terminal_initialize();

        printf("%d hello, another string is: %s, and then another char is: %c and this is try: %a here is another try: %s", 5123, "string string", 'c', "a try");

        while(1) {}
    }
}
