#include <stddef.h>

#include "vga_buffer.hpp"
#include "utils.hpp"

typedef enum vga_color
{
    VGA_COLOR_BLACK = 0,
    VGA_COLOR_BLUE = 1,
    VGA_COLOR_GREEN = 2,
    VGA_COLOR_CYAN = 3,
    VGA_COLOR_RED = 4,
    VGA_COLOR_MAGENTA = 5,
    VGA_COLOR_BROWN = 6,
    VGA_COLOR_LIGHT_GREY = 7,
    VGA_COLOR_DARK_GREY = 8,
    VGA_COLOR_LIGHT_BLUE = 9,
    VGA_COLOR_LIGHT_GREEN = 10,
    VGA_COLOR_LIGHT_CYAN = 11,
    VGA_COLOR_LIGHT_RED = 12,
    VGA_COLOR_LIGHT_MAGENTA = 13,
    VGA_COLOR_LIGHT_BROWN = 14,
    VGA_COLOR_WHITE = 15,
} vga_color;

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) {
    return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color) {
    return (uint16_t)uc | (uint16_t)color << 8;
}

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static uint16_t* terminal_buffer;

static void handle_new_line() {
    terminal_row++;
    terminal_column = 0;
}

void terminal_setcolor(uint8_t color) {
	terminal_color = color;
}

void terminal_initialize() {
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = (uint16_t*) 0xB8000;

	for (size_t i = 0; i < VGA_HEIGHT; i++) {
		for (size_t j = 0; j < VGA_WIDTH; j++) {
			const size_t index = i * VGA_WIDTH + j;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

static void terminal_putentryat(char c) {
	const size_t index = terminal_row * VGA_WIDTH + terminal_column;
	terminal_buffer[index] = vga_entry(c, terminal_color);
}

static void handle_filled_vga_height(void) {
	terminal_row = 0;
}

void terminal_putchar(const char c) {
    if(c == '\n') {
        handle_new_line();
    } else {
        terminal_putentryat(c);
        if (++terminal_column == VGA_WIDTH) {
            handle_new_line();
	    }
    }

    if (terminal_row == VGA_HEIGHT) {
        handle_filled_vga_height();
    }
}

void terminal_print_string(const char * data) {
   	for (size_t i = 0; i < strlen(data); i++) {
		terminal_putchar(data[i]);
    }
}

void terminal_print_int(const int number) {
    char buffer[64];

    itoa(number, buffer);

    terminal_print_string(buffer);
}

void terminal_print_hex(const int value) {
    unsigned int mask = 0xF0000000; // Mask for the most significant hex digit

    terminal_print_string("0x");

    for (int i = 0; i < 8; i++) {
        unsigned int hex_digit = (value & mask) >> (28 - (i * 4));
        if (hex_digit < 10) {
            terminal_print_int(hex_digit);
        }
        else {
            terminal_putchar('A' + (hex_digit - 10));
        }

        mask >>= 4;
    }
}
