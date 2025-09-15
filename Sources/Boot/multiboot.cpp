#include <stddef.h>

#include "Boot/multiboot.hpp"
#include "Utils/Functions/PrintUtils.hpp"
#include "KernelException.hpp"

#define NEXT_TAG(tag) (tag->size + 7) & ~7

Multiboot::Multiboot(uint32_t magic, uintptr_t addr) : _magic(magic), _addr(addr)
{}

MemoryRegion Multiboot::find_usable_region() const
{
    this->validate_multiboot_magic();

    uintptr_t kernel_end = reinterpret_cast<uintptr_t>(&__end);
    const uintptr_t page = 0x1000;

    uintptr_t chosen_base = 0;
    size_t chosen_size = 0;

    multiboot_info_t *mb_info = (multiboot_info_t *) _addr;
    uint8_t *tag_ptr = (uint8_t * ) & mb_info->tags[0];
    struct multiboot_tag* tag = nullptr;
    for (tag = reinterpret_cast<multiboot_tag *>(tag_ptr);
         tag->type != MULTIBOOT_TAG_TYPE_END;
         tag = reinterpret_cast<multiboot_tag *>(reinterpret_cast<uint8_t *>(tag) + (NEXT_TAG(tag))))
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
                if (entry->type != MULTIBOOT_MEMORY_AVAILABLE) continue; // not usable

                uintptr_t found_entry_base = (uintptr_t) entry->addr;
                size_t found_entry_length = (size_t) entry->len;
                const uintptr_t &found_entry_end = found_entry_base + found_entry_length;

                bool is_kernel_inside_entry = kernel_end >= found_entry_base && kernel_end < found_entry_end;

                // Option A: pick space after kernel
                if (is_kernel_inside_entry)
                {
                    uintptr_t heap_base = (kernel_end + (page - 1)) & ~(page - 1); // page align up
                    size_t heap_size = found_entry_end - heap_base;
                    if (heap_size > 0)
                    {
                        chosen_base = heap_base;
                        chosen_size = heap_size;
                        goto got_region; // best case, stop
                    }
                }

                // Option B: otherwise consider this entry as a candidate (largest)
                if (found_entry_length > chosen_size)
                {
                    chosen_base = found_entry_base;
                    chosen_size = found_entry_length;
                }
            }
        }
    }

    got_region:
    if (chosen_size == 0)
    {
        return MemoryRegion{0, 0};
    }

    // If chosen_base is below kernel_end, bump it to after kernel
    if (chosen_base < kernel_end)
    {
        uintptr_t new_base = (kernel_end + (page - 1)) & ~(page - 1);
        if (new_base >= chosen_base + chosen_size)
        {
            // no room after kernel in this region
            return MemoryRegion{0, 0};
        }
        chosen_size -= (new_base - chosen_base);
        chosen_base = new_base;
    }

    return MemoryRegion{chosen_base, chosen_size};
}


void Multiboot::validate_multiboot_magic() const
{
    if (_magic != MULTIBOOT2_BOOTLOADER_MAGIC)
    {
        PrintUtils::printk("Invalid _magic number: %x\n", _magic);
        THROW_KERNEL_EXCEPTION();
    }
}
