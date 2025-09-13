// Check if the compiler thinks you are targeting the wrong operating system.
#ifdef __linux__
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

// Check if compiled with the right compiler
#ifndef __x86_64__
#error "This OS needs to be compiled with a x86_64-elf compiler"
#endif

#include "Boot/multiboot.h"
#include "VgaBuffer.hpp"
#include "Utils/Functions/PrintUtils.hpp"
#include "Interrupts/InterruptsDescriptorTable.hpp"
#include "Interrupts/InterruptHandlersGenerator/InterruptHandlersGenerator.hpp"

void parse_multiboot_info(const uint32_t &magic, const uintptr_t &addr)
{
    if (magic != MULTIBOOT2_BOOTLOADER_MAGIC)
    {
        PrintUtils::printk("Invalid magic number: %x\n", magic);
        THROW_KERNEL_EXCEPTION();
    }

    multiboot_info_t *mb_info = (multiboot_info_t *) addr;
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
                // use cmd->string
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
                // handle framebuffer info if you requested it
                break;
            }
            default:
                PrintUtils::printk("Unknown tag type %d\n", tag->type);
                // ignore unknown tag
                break;
        }

        // advance to next tag (8-byte aligned)
        ptr += (tag->size + 7) & ~7;
    }
}

extern "C"
{
    void kernel_main(uint32_t magic, uintptr_t addr)
	{
        Terminal::get().initialize();
        parse_multiboot_info(magic, addr);

        InterruptHandlersGenerator interruptHandlersGenerator;
        InterruptDescriptorTable idt;

        PrintUtils::printk("[*] Interrupt table initialized.\n");

        asm volatile("int $3");
        asm volatile (".word 0xFFFF");
        PrintUtils::printk("%d\n", 1 / 0);
		while (1);
	}
}
