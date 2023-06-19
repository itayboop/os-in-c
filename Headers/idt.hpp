#pragma once

#include <stdint.h>

struct idt_entry_64 {
    uint16_t offset_low;       // offset bits 0..15
    uint16_t selector;       // a code segment selector in GDT or LDT
    uint8_t ist;             // bits 0..2 holds Interrupt Stack Table offset, rest of bits zero.
    uint8_t type_attributes; // gate type, dpl, and p fields
    uint16_t offset_mid;       // offset bits 16..31
    uint32_t offset_high;       // offset bits 32..63
    uint32_t zero;           // reserved
} __attribute__((packed));

#define IDT_64BIT_INTERRUPT_GATE 0xE
#define IDT_STORAGE_SEGMENT 0x20
#define IDT_DPL_3 0x60
#define IDT_PRESENT 0x80

#define INT_END asm volatile("iretq");

extern void idt_init();
extern void exceptions_init();
extern void idt_register_interrupt(uint8_t i, uint32_t addr);
extern void add_idt_descriptor(uint8_t id, idt_entry_64 desc);
