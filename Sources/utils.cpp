#define MAX_DIGITS 62

#include <stdarg.h>
#include "vga_buffer.hpp"
#include "utils.hpp"

void printf(const char * formatted_str, ...) {
    va_list arg;
    char c;

    va_start(arg, formatted_str);

    while ((c = *formatted_str++)) {
        if(c != '%') {
            terminal_putchar(c);
        } else {
            c = *formatted_str++;

            switch (c) {
                case 'd':
                {
                    int number_to_print = va_arg(arg, int);
                    terminal_print_int(number_to_print);
                }
                    break;
                case 's':
                {
                    char * string_to_print = va_arg(arg, char *);
                    terminal_print_string(string_to_print);
                }
                    break;
                case 'c':
                {
                    char char_to_print = va_arg(arg, int); // 'char' is promoted to 'int' when passed through '...'
                    terminal_putchar(char_to_print);
                }
                    break;
                default:
                    break;
            }
        }
    }

    va_end(arg);
}

void itoa(int num, char * str) {
    int i = 0;
    int is_negative = 0;

    if (0 > num) {
        is_negative = 1;
        num = 0 - num;
    }

    do {
        str[i++] = num % 10 + '0';
        num /= 10;
    } while (num && MAX_DIGITS > i); // 62 since we add may add '-' and null terminator at the end.


    if (is_negative) {
        str[i++] = '-';
    }

    str[i] = '\0';

    for (int j = 0; j < i / 2; j++) {
        char temp = str[j];
        str[j] = str[i - j - 1];
        str[i - j - 1] = temp;
    }
}

size_t strlen(const char* str) {
    size_t string_length = 0;

    while(str[string_length]) {
        string_length++;
    }

    return string_length;
}