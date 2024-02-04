#pragma once

#include "Utils/Vector.hpp"

template<typename T, uint32_t MAX_SIZE>
constexpr Vector<T, MAX_SIZE>::Vector(const T* arr, uint32_t size) : Vector(size)
{
    for (uint32_t i = 0; i < _count; ++i)
    {
        _arr[i] = arr[i];
    }
}

template<typename T, uint32_t MAX_SIZE>
constexpr Vector<T, MAX_SIZE>::Vector(uint32_t initial_size) : Vector()
{
    resize(initial_size);
}

template<typename T, uint32_t MAX_SIZE>
void Vector<T, MAX_SIZE>::push_back(const T& value)
{
    if (_count == MAX_SIZE)
    {
        THROW_KERNEL_EXCEPTION();
    }

    _arr[++_count] = value;
}

template<typename T, uint32_t MAX_SIZE>
constexpr void Vector<T, MAX_SIZE>::resize(uint32_t new_size)
{
    if (new_size > MAX_SIZE)
    {
        THROW_KERNEL_EXCEPTION();
    }

    _count = new_size;
}
