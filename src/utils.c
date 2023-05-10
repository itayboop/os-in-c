#include "utils.h"

size_t strlen(const char* str) {
    size_t string_length = 0;

    while(str[string_length]) {
        string_length++;
    }

    return string_length;
}