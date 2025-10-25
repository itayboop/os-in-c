#include <stddef.h>

#include "Boot/multiboot.hpp"
#include "Utils/Functions/PrintUtils.hpp"
#include "KernelException.hpp"

#define NEXT_TAG(tag) (tag->size + 7) & ~7

Multiboot::Multiboot(uint32_t magic, uintptr_t addr) : _magic(magic), _addr(addr)
{
    this->validate_multiboot_magic();
}

MemoryRegion Multiboot::allocate_after_kernel(MemoryRegion candidate_region) const
{
    const uintptr_t candidate_region_end = candidate_region.base + candidate_region.length;
    bool is_kernel_inside_entry = KERNEL_END >= candidate_region.base && KERNEL_END < candidate_region_end;

    if (is_kernel_inside_entry)
    {
        uintptr_t heap_base = (KERNEL_END + (_PAGE_SIZE - 1)) & ~(_PAGE_SIZE - 1);
        size_t heap_size = candidate_region_end - heap_base;
        if (heap_size > 0)
        {
            // this is the best case, so we stop
            return MemoryRegion{heap_base, heap_size};
        }
    }

    return MemoryRegion{0, 0};
}

MemoryRegion Multiboot::pick_largest_region(MemoryRegion candidate_region, size_t current_best_size) const
{
    if (candidate_region.length > current_best_size) {
        return MemoryRegion{candidate_region.base, candidate_region.length};
    }

    return MemoryRegion{0, 0};
}

MemoryRegion Multiboot::align_region_away_from_kernel(MemoryRegion region) const
{
    if (region.length == 0)
    {
        return region;
    }

    if (region.base < KERNEL_END) {
        uintptr_t new_base = (KERNEL_END + (_PAGE_SIZE - 1)) & ~(_PAGE_SIZE - 1);

        if (new_base >= region.base + region.length) {
            return MemoryRegion{0, 0};
        }

        region.length -= (new_base - region.base);
        region.base = new_base;
    }

    return region;
}

MemoryRegion Multiboot::find_usable_region() const
{
    MemoryRegion best_region{0, 0};

    multiboot_info_t *mb_info = (multiboot_info_t *) _addr;
    uint8_t *tag_ptr = (uint8_t *) &mb_info->tags[0];

    for (struct multiboot_tag *tag = reinterpret_cast<multiboot_tag *>(tag_ptr);
         tag->type != MULTIBOOT_TAG_TYPE_END;
         tag = reinterpret_cast<multiboot_tag *>(
                 reinterpret_cast<uint8_t *>(tag) + (NEXT_TAG(tag))))
    {
        if (tag->type == MULTIBOOT_TAG_TYPE_MMAP)
        {
            auto *mmap_tag = reinterpret_cast<multiboot_tag_mmap *>(tag);
            auto *entry = reinterpret_cast<multiboot_mmap_entry *>(mmap_tag + 1);

            uint8_t *entries_end = reinterpret_cast<uint8_t *>(mmap_tag) + mmap_tag->size;
            for (; reinterpret_cast<uint8_t *>(entry) < entries_end;
                   entry = reinterpret_cast<multiboot_mmap_entry *>(
                           reinterpret_cast<uint8_t *>(entry) + mmap_tag->entry_size))
            {
                if (entry->type != MULTIBOOT_MEMORY_AVAILABLE) continue;

                uintptr_t found_entry_start = (uintptr_t) entry->addr;
                size_t found_entry_length = (size_t) entry->len;
                MemoryRegion candidate_region{(uintptr_t) entry->addr, (size_t) entry->len};

                MemoryRegion after_kernel = this->allocate_after_kernel(candidate_region); // best case, so we stop here
                if (after_kernel.length > 0)
                {
                    return after_kernel;
                }

                MemoryRegion candidate = pick_largest_region(candidate_region, best_region.length);
                if (candidate.length > 0) {
                    best_region = candidate;
                }
            }
        }
    }

    return this->align_region_away_from_kernel(best_region);
}

void Multiboot::validate_multiboot_magic() const
{
    if (_magic != MULTIBOOT2_BOOTLOADER_MAGIC)
    {
        PrintUtils::printk("Invalid _magic number: %x\n", _magic);
        THROW_KERNEL_EXCEPTION();
    }
}

