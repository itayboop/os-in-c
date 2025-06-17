#pragma once

#include <stdint.h>

typedef struct __attribute__((packed)) InterruptDescriptorTableEntry
{
    uint16_t offset_low;    // offset bits 0..15
    uint16_t selector;    // a code segment selector in GDT
    uint8_t ist_index;
    uint8_t type_attributes;
    uint16_t offset_mid;    // offset bits 16..31
    uint32_t offset_high;    // offset bits 32..63
    uint32_t reserved;
} InterruptDescriptorTableEntry;

typedef struct __attribute__((packed)) InterruptDescriptorTablePtr
{
    uint16_t size;
    uintptr_t base;
} InterruptDescriptorTablePtr;


extern "C" void load_interrupt_descriptor_table(InterruptDescriptorTablePtr *ptr);

class IDT
{
private:
    InterruptDescriptorTablePtr _interrupt_descriptor_table_ptr __attribute__((aligned(16)));
    InterruptDescriptorTableEntry _interrupt_descriptor_table[256] __attribute__((aligned(16)));

private:
    void set_gate(uint8_t entry_number, uintptr_t funcall);
    void set_all_gates();

public:
    void initialize();
};
