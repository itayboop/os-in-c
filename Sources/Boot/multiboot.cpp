#include "Boot/multiboot.hpp"
#include "Utils/Functions/PrintUtils.hpp"
#include "KernelException.hpp"

#define NEXT_TAG(tag) (tag->size + 7) & ~7

Multiboot::Multiboot(uint32_t magic, uintptr_t addr) : _magic(magic), _addr(addr)
{}

void Multiboot::parse_mb_info() const
{
    this->validate_multiboot_magic();

    multiboot_info_t *mb_info = (multiboot_info_t *) _addr;
    uint8_t *ptr = (uint8_t *) &mb_info->tags[0];
    while (1) {
        struct multiboot_tag *tag = (struct multiboot_tag *) ptr;

        if (tag->type == MULTIBOOT_TAG_TYPE_END) {
            break;
        }

        switch (tag->type) {
            case MULTIBOOT_TAG_TYPE_CMDLINE: {
                struct multiboot_tag_string *cmd = (struct multiboot_tag_string *) tag;
                PrintUtils::printk("Command line tag found, cmdline: %s\n", cmd->string);
                break;
            }
            case MULTIBOOT_TAG_TYPE_MMAP: {
                struct multiboot_tag_mmap *mmap = (struct multiboot_tag_mmap *) tag;
                PrintUtils::printk("Memory map tag found, size: %d\n", mmap->size);
                // walk mmap->entries[...] here
                break;
            }
            case MULTIBOOT_TAG_TYPE_FRAMEBUFFER: {
                PrintUtils::printk("Framebuffer info tag found!\n");
                break;
            }
            default:
                PrintUtils::printk("Unknown tag type %d\n", tag->type);
                // ignore unknown tag
                break;
        }

        ptr += NEXT_TAG(tag);
    }
}

void Multiboot::validate_multiboot_magic() const
{
    if (_magic != MULTIBOOT2_BOOTLOADER_MAGIC)
    {
        PrintUtils::printk("Invalid _magic number: %x\n", _magic);
        THROW_KERNEL_EXCEPTION();
    }
}
