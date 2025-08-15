#pragma once
#include <stdint.h>

namespace HexUtils
{
    constexpr unsigned int extract_nibble(int value, int index_from_left)
    {
        return (value >> (28 - (index_from_left * 4))) & 0xF;
    }
}
