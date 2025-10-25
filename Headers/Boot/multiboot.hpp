#pragma once

#include <stdint.h>
#include "multiboot_types.h"

#define KERNEL_END ((uintptr_t)&__end)

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

private:
    void validate_multiboot_magic() const;

    MemoryRegion allocate_after_kernel(MemoryRegion candidate_region) const;
    MemoryRegion pick_largest_region(MemoryRegion candidate_region, size_t current_best_size) const;
    MemoryRegion align_region_away_from_kernel(MemoryRegion region) const;

private:
    static constexpr size_t _PAGE_SIZE = 0x1000;
    uint32_t _magic;
    uintptr_t _addr;

};