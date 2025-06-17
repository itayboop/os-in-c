#pragma once
#include <stdint.h>

void terminal_print_string(const char *str);
void terminal_print_int(const int number);
void terminal_print_hex(const int number);
void terminal_putchar(const char c);
void terminal_initialize();
