#pragma once

#include <stdint.h>

void terminal_initialize(void);
void terminal_putchar(char c);
void terminal_write_string(const char* data);
void terminal_setcolor(uint8_t color);
