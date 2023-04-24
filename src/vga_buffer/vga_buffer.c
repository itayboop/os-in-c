#include <stddef.h>
#include <stdint.h>

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

static void handle_new_line(void) {
    terminal_row++;
    terminal_column = 0;
}

void terminal_setcolor(uint8_t color) {
	terminal_color = color;
}

void terminal_initialize(void) {
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

static void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) {
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

static void handle_filled_vga_height(void) {
	terminal_row = 0;
}

void terminal_putchar(char c) {
    if(c == '\n') {
        handle_new_line();
    } else {
        terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
        if (++terminal_column == VGA_WIDTH) {
		    terminal_column = 0;
            terminal_row++;
	    }
    }

    if (terminal_row == VGA_HEIGHT) {
        handle_filled_vga_height();
    }
}

static void terminal_write(const char* data, size_t size)  {
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}

void terminal_write_string(const char* data) {
	terminal_write(data, strlen(data));
}