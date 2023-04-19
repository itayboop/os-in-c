#ifndef VGA_BUFFER_H
#define VGA_BUFFER_H

void terminal_initialize(void);
void terminal_putchar(char c);
void terminal_write_string(const char* data);
void terminal_setcolor(uint8_t color);

#endif
