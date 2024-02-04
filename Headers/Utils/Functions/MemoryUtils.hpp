#pragma once
#include "stddef.h"

class MemoryUtils
{
public:
    template <typename T>
    static T* memset(T* ptr, char c, size_t size);
};
