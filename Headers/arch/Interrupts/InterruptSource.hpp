#pragma once
#include "InterruptsDescriptorTable.hpp"

class InterruptSource {
public:
    virtual void register_handlers(InterruptDescriptorTable &idt) = 0;
    virtual ~InterruptSource() = default;
    // TODO: add virtual destructor when memory management is implemented
};

class RAM
{
public:
    void* allocate(size_t bytes_count);
    void deallocate(void* buffer);

private:
    uint8_t buffer[SIZE];
};

RAM g__ram;

void* malloc(size_t size);
void free(void* buffer);

void* operator new(size_t size);
