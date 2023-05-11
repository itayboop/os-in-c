#pragma once

#include <stdint.h>

void terminal_initialize(void);
void terminal_putchar(char c);
void terminal_print_string(const char *str);
void terminal_print_int(const int number);
void terminal_setcolor(uint8_t color);
