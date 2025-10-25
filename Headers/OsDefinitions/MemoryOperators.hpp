#pragma once

#include "MemoryAllocator.hpp"
#include "OsDefinitions/TypeTraits.hpp"
#include "KernelException.hpp"

void* operator new(std::size_t count, const std::nothrow_t&) noexcept {
    return MemoryAllocator::get().malloc(count);
}

void* operator new(std::size_t count) {
    void *ptr = MemoryAllocator::get().malloc(count);
    if (!ptr) {
        THROW_KERNEL_EXCEPTION();
    }
    return ptr;
}

void operator delete(void *ptr) noexcept {
    if (ptr) MemoryAllocator::get().free(ptr);
}

void operator delete(void *ptr, std::size_t) noexcept {
    if (ptr) MemoryAllocator::get().free(ptr);
}

void operator delete(void *ptr, const std::nothrow_t&) noexcept {
    if (ptr) MemoryAllocator::get().free(ptr);
}

void* operator new[](std::size_t count) {
    void *ptr = MemoryAllocator::get().malloc(count);
    if (!ptr) {
        THROW_KERNEL_EXCEPTION();
    }
    return ptr;
}

void* operator new[](std::size_t count, const std::nothrow_t&) noexcept {
    return MemoryAllocator::get().malloc(count);
}

void operator delete[](void *ptr) noexcept {
    if(ptr) MemoryAllocator::get().free(ptr);
}


void operator delete[](void *ptr, std::size_t) noexcept {
    if(ptr) MemoryAllocator::get().free(ptr);
}

void operator delete[](void *ptr, const std::nothrow_t&) noexcept {
    if(ptr) MemoryAllocator::get().free(ptr);
}
