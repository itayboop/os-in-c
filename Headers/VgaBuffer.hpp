#pragma once

#include <stdint.h>

typedef enum vga_color
{
    BLACK = 0,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    LIGHT_GREY,
    DARK_GREY,
    LIGHT_BLUE,
    LIGHT_GREEN,
    LIGHT_CYAN,
    LIGHT_RED,
    LIGHT_MAGENTA,
    LIGHT_BROWN,
    WHITE,
} vga_color;

void terminal_print_string(const char *str);
void terminal_print_int(const int number);
void terminal_print_hex(const int number);
void terminal_putchar(const char c);
void terminal_initialize();
