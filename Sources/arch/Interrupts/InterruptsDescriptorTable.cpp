#include <stdint.h>

#include "Utils/Functions/MemoryUtils.hpp"
#include "arch/Interrupts/InterruptsDescriptorTable.hpp"


InterruptDescriptorTable::InterruptDescriptorTable()
{
    this->initialize();
}

void InterruptDescriptorTable::set_gate(uint8_t entry_number, uintptr_t funcall)
{
    InterruptDescriptorTableEntry *entry = &this->table[entry_number];

    entry->offset_high = (funcall >> 32) & 0xFFFFFFFF;
    entry->offset_mid = (funcall >> 16) & 0xFFFF;
    entry->offset_low = funcall & 0xFFFF;
    entry->type_attributes = 0xEF;
    entry->ist_index = 0;
    entry->selector = 8; // CODE descriptor, see gdt64.code
}

void InterruptDescriptorTable::initialize()
{
    MemoryUtils::memset(this->table, 0, this->IDT_TABLE_SIZE);
    this->ptr.size = sizeof(this->table) / sizeof(this->table[0]);
    this->ptr.base = this->table;

    load_interrupt_descriptor_table(&this->ptr);
}
