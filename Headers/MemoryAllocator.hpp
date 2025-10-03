#pragma once

#include <stddef.h>
#include <stdint.h>

#include "Utils/Functions/PrintUtils.hpp"

class MemoryAllocator final
{
public:
    static MemoryAllocator &get()
    {
        static MemoryAllocator allocator;
        return allocator;
    }

public:
    void init(void *base, size_t size)
    {
        _heap_base = reinterpret_cast<uint8_t *>(base);
        _heap_size = size;
        _heap_current = _heap_base;
    }

    void *malloc(size_t size)
    {
        if (!_heap_base)
        {
            PrintUtils::printk("Heap not initialized!\n");
            return nullptr;
        }

        size = (size + 15) & ~((size_t) 15);

        if (_heap_current + size > _heap_base + _heap_size)
        {
            PrintUtils::printk("Out of memory!\n");
            return nullptr;
        }

        void *ptr = _heap_current;
        _heap_current += size;
        return ptr;
    }

    // TODO: implement
    void free(void *)
    {
        // no-op for bump allocator
    }

private:
    MemoryAllocator() = default;
    MemoryAllocator(const MemoryAllocator &) = delete;
    MemoryAllocator &operator=(const MemoryAllocator &) = delete;

private:
    uint8_t *_heap_base = nullptr;
    size_t _heap_size = 0;
    uint8_t *_heap_current = nullptr;
};