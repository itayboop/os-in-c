#pragma once
#include "stddef.h"

class MemoryUtils
{
public:
    static void* memset(void* addr, char c, size_t size);
};
