#pragma once

#include <stdint.h>
#include "multiboot_types.h"

extern "C" char __end;

struct MemoryRegion
{
    uintptr_t base;
    size_t length;
};

class Multiboot final
{
public:
    Multiboot(uint32_t magic, uintptr_t addr);

public:
    MemoryRegion find_usable_region() const;
    void validate_multiboot_magic() const;

private:
    uint32_t _magic;
    uintptr_t _addr;

};