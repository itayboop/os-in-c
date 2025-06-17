#pragma once

#include <stdint.h>

namespace HexUtils
{
    static constexpr unsigned int extract_nibble(uint32_t value, int index_from_left)
    {
        return (value >> (28 - (index_from_left * 4))) & 0xF;
    }
}