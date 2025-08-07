#pragma once

#include "macros.h"
#include "Utils/Span.hpp"

struct InterruptDescriptorTableEntry
{
    uint16_t offset_low;    // offset bits 0..15
    uint16_t selector;    // a code segment selector in GDT
    uint8_t ist_index;
    uint8_t type_attributes;
    uint16_t offset_mid;    // offset bits 16..31
    uint32_t offset_high;    // offset bits 32..63
    uint32_t reserved;
} PACKED;

struct InterruptDescriptorTablePtr
{
    uint16_t size;
    uintptr_t base; // TODO - change the type to a pointer type
} PACKED;

extern "C"
void load_interrupt_descriptor_table(InterruptDescriptorTablePtr *ptr);

class InterruptDescriptorTable
{
public:
    InterruptDescriptorTable();

private:
    static constexpr int IDT_TABLE_SIZE = 256;

    InterruptDescriptorTablePtr ptr __attribute__((aligned(16)));
    InterruptDescriptorTableEntry table[IDT_TABLE_SIZE] __attribute__((aligned(16)));

private:
    void set_gate(uint8_t entry_number, uintptr_t funcall);
    void set_all_gates();
    void initialize();
};
