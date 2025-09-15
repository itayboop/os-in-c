#include "memory.hpp"
#include "Utils/Functions/PrintUtils.hpp"

#include <stdint.h>

extern "C" {

// Define the heap region manually (linker script should place this correctly)
static uint8_t *heap_base = nullptr;
static size_t heap_size = 0;

static uint8_t *heap_current = nullptr;

void init_heap(void *base, size_t size)
{
    heap_base = reinterpret_cast<uint8_t *>(base);
    heap_size = size;
    heap_current = heap_base;
}

void *malloc(size_t size)
{
    if (!heap_base)
    {
        PrintUtils::printk("Heap not initialized!\n");
        return nullptr;
    }

    // Align to 16 bytes (good practice for most CPUs)
    size = (size + 15) & ~((size_t) 15);

    bool out_of_memory = heap_current + size > heap_base + heap_size;
    if (out_of_memory)
    {
        PrintUtils::printk("Out of memory!\n");
        return nullptr;
    }

    void *ptr = heap_current;
    heap_current += size;
    return ptr;
}

void free(void *)
{
    // no-op for bump allocator
}

}
