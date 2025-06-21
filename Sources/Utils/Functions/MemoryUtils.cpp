#include "Utils/Functions/MemoryUtils.hpp"

void * MemoryUtils::memset(void *ptr, int value, unsigned long num) {
    unsigned char *p = static_cast<unsigned char*>(ptr);
    for (unsigned long i = 0; i < num; ++i) {
        p[i] = static_cast<unsigned char>(value);
    }
    return ptr;
}