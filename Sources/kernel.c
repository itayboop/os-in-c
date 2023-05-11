#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "vga_buffer.h"
#include "utils.h"

/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

extern "C" {
void kernel_main(void) {
    terminal_initialize();

    printf("%d hello, another string is: %s, and then another char is: %c and this is try: %a here is another try: %s", 5123, "string string", 'c', "a try");

    while(1) {}
}
}
