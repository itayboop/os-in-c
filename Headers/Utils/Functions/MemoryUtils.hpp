#pragma once
#include "stddef.h"

namespace MemoryUtils
{
    template <typename T>
    constexpr T* memset(T* ptr, char c, size_t size)
    {
        unsigned char* byte_ptr = (unsigned char *)ptr;
        unsigned char byte_value = (unsigned char)c;

        for(unsigned int i = 0; i < size; i++)
        {
            byte_ptr[i] = byte_value;
        }

        return ptr;
    };
};
