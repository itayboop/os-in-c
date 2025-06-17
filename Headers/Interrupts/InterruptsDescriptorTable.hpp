#pragma once

#include <stdint.h>

typedef struct __attribute__((packed)) idt_entry_64_s
{
    uint16_t offset_low;    // offset bits 0..15
    uint16_t selector;    // a code segment selector in GDT
    uint8_t ist_index;
    uint8_t type_attributes;
    uint16_t offset_mid;    // offset bits 16..31
    uint32_t offset_high;    // offset bits 32..63
    uint32_t reserved;
} idt_entry_64_t;

typedef struct __attribute__((packed)) idt_64_pointer_s
{
    uint16_t size;
    uintptr_t base;
} idt_64_pointer_t;


extern "C" void load_idt(idt_64_pointer_t *ptr);

class IDT
{
private:
    idt_64_pointer_t idt_ptr __attribute__((aligned(16)));
    idt_entry_64_t idt[256] __attribute__((aligned(16)));

private:
    void set_gate(uint8_t entry_number, uintptr_t funcall);
    void set_all_gates();

public:
    void initialize();
};
