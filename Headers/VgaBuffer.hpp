#pragma once

#include <stddef.h>
#include <stdint.h>

enum VgaColor {
    BLACK = 0,
    BLUE = 1,
    GREEN = 2,
    CYAN = 3,
    RED = 4,
    MAGENTA = 5,
    BROWN = 6,
    LIGHT_GREY = 7,
    DARK_GREY = 8,
    LIGHT_BLUE = 9,
    LIGHT_GREEN = 10,
    LIGHT_CYAN = 11,
    LIGHT_RED = 12,
    LIGHT_MAGENTA = 13,
    LIGHT_BROWN = 14,
    WHITE = 15
};

class Terminal {
public:
    static Terminal & get();

    void initialize();
    void put_char(char c);
    void print(const char* str);
    void print_int(int number);
    void print_hex(int value);

private:
    Terminal();
    Terminal(const Terminal&) = delete;
    Terminal& operator=(const Terminal&) = delete;

    static constexpr size_t WIDTH = 80;
    static constexpr size_t HEIGHT = 25;

    size_t row;
    size_t column;
    uint8_t color;
    volatile uint16_t* buffer;

    void put_entry_at(char c);
    void new_line();
    void handle_scroll();
    uint8_t entry_color(VgaColor fg, VgaColor bg);
    uint16_t make_entry(unsigned char uc, uint8_t color);
};
