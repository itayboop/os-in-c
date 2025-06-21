#include "VgaBuffer.hpp"
#include "Utils/Functions/HexUtils.hpp"
#include "Utils/Functions/StringsUtils.hpp"

Terminal & Terminal::get() {
    static Terminal instance;
    return instance;
}

Terminal::Terminal() {
    buffer = reinterpret_cast<uint16_t*>(0xB8000);
    row = 0;
    column = 0;
    color = entry_color(LIGHT_GREY, BLACK);
}

void Terminal::initialize() {
    for (size_t y = 0; y < HEIGHT; y++) {
        for (size_t x = 0; x < WIDTH; x++) {
            const size_t index = y * WIDTH + x;
            buffer[index] = make_entry(' ', color);
        }
    }
}

void Terminal::put_char(char c) {
    if (c == '\n') {
        new_line();
    } else {
        put_entry_at(c);
        if (++column == WIDTH) {
            new_line();
        }
    }

    if (row == HEIGHT) {
        handle_scroll();
    }
}

void Terminal::put_entry_at(char c) {
    const size_t index = row * WIDTH + column;
    buffer[index] = make_entry(c, color);
}

void Terminal::new_line() {
    row++;
    column = 0;
}

void Terminal::handle_scroll() {
    // for now, just reset (can implement actual scrolling later)
    row = 0;
}

void Terminal::print(const char* str) {
    for (size_t i = 0; i < StringsUtils::strlen(str); i++) {
        put_char(str[i]);
    }
}

void Terminal::print_int(int number) {
    char buffer[64];
    StringsUtils::itoa(number, buffer);
    print(buffer);
}

void Terminal::print_hex(int value) {
    print("0x");
    unsigned int mask = 0xF0000000;

    for (unsigned int i = 0; i < 8; i++) {
        unsigned int hex_digit = HexUtils::extract_nibble(value, i);
        if (hex_digit < 10) {
            put_char('0' + hex_digit);
        } else {
            put_char('A' + (hex_digit - 10));
        }

        mask >>= 4;
    }
}

uint8_t Terminal::entry_color(VgaColor fg, VgaColor bg) {
    return fg | (bg << 4);
}

uint16_t Terminal::make_entry(unsigned char uc, uint8_t color) {
    return static_cast<uint16_t>(uc) | (static_cast<uint16_t>(color) << 8);
}
