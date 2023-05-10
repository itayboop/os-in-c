#include <stdarg.h>
#include "vga_buffer.h"
#include "utils.h"

void printf(const char * formatted_str, ...) {
    va_list arg;
    char c;

    va_start(arg, formatted_str);

    while ((c = *formatted_str++)) {
        if(c != '%') {
            terminal_putchar(c);
            continue;
        }

        c = *formatted_str++;

        switch (c) {
            case 'd':
                int number_to_print = va_arg(arg, int);
                terminal_print_int(number_to_print);

                break;
            case 's':
                char * string_to_print = va_arg(arg, char *);
                terminal_print_string(string_to_print);

                break;
            case 'c':
                char char_to_print = va_arg(arg, int); // 'char' is promoted to 'int' when passed through '...'
                terminal_putchar(char_to_print);

                break;
            default:
                char * non_formatted_string = va_arg(arg, char *);
                terminal_putchar('%');
                terminal_print_string(non_formatted_string);

                break;
        }
    }

    va_end(arg);
}

size_t strlen(const char* str) {
    size_t string_length = 0;

    while(str[string_length]) {
        string_length++;
    }

    return string_length;
}