#include <stdint.h>

#include "Utils/Functions/MemoryUtils.hpp"
#include "Interrupts/InterruptsDescriptorTable.hpp"
#include "Interrupts/InterruptHandlersGenerator/InterruptHandlersGenerator.hpp"


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

void InterruptDescriptorTable::set_all_gates()
{
    this->set_gate(0, (uintptr_t) isr0);
    this->set_gate(1, (uintptr_t) isr1);
    this->set_gate(2, (uintptr_t) isr2);
    this->set_gate(3, (uintptr_t) isr3);
    this->set_gate(4, (uintptr_t) isr4);
    this->set_gate(5, (uintptr_t) isr5);
    this->set_gate(6, (uintptr_t) isr6);
    this->set_gate(7, (uintptr_t) isr7);
    this->set_gate(8, (uintptr_t) isr8);
    this->set_gate(9, (uintptr_t) isr9);
    this->set_gate(10, (uintptr_t) isr10);
    this->set_gate(11, (uintptr_t) isr11);
    this->set_gate(12, (uintptr_t) isr12);
    this->set_gate(13, (uintptr_t) isr13);
    this->set_gate(14, (uintptr_t) isr14);
    this->set_gate(15, (uintptr_t) isr15);
    this->set_gate(16, (uintptr_t) isr16);
    this->set_gate(17, (uintptr_t) isr17);
    this->set_gate(18, (uintptr_t) isr18);
    this->set_gate(19, (uintptr_t) isr19);
    this->set_gate(20, (uintptr_t) isr20);
    this->set_gate(21, (uintptr_t) isr21);
    this->set_gate(22, (uintptr_t) isr22);
    this->set_gate(23, (uintptr_t) isr23);
    this->set_gate(24, (uintptr_t) isr24);
    this->set_gate(25, (uintptr_t) isr25);
    this->set_gate(26, (uintptr_t) isr26);
    this->set_gate(27, (uintptr_t) isr27);
    this->set_gate(28, (uintptr_t) isr28);
    this->set_gate(29, (uintptr_t) isr29);
    this->set_gate(30, (uintptr_t) isr30);
    this->set_gate(31, (uintptr_t) isr31);
    this->set_gate(32, (uintptr_t) isr32);
    this->set_gate(33, (uintptr_t) isr33);
    this->set_gate(34, (uintptr_t) isr34);
    this->set_gate(35, (uintptr_t) isr35);
    this->set_gate(36, (uintptr_t) isr36);
    this->set_gate(37, (uintptr_t) isr37);
    this->set_gate(38, (uintptr_t) isr38);
    this->set_gate(39, (uintptr_t) isr39);
    this->set_gate(40, (uintptr_t) isr40);
    this->set_gate(41, (uintptr_t) isr41);
    this->set_gate(42, (uintptr_t) isr42);
    this->set_gate(43, (uintptr_t) isr43);
    this->set_gate(44, (uintptr_t) isr44);
    this->set_gate(45, (uintptr_t) isr45);
    this->set_gate(46, (uintptr_t) isr46);
    this->set_gate(47, (uintptr_t) isr47);
}

void InterruptDescriptorTable::initialize() // Move this to the constructor
{
    MemoryUtils::memset(this->table, 0, this->IDT_TABLE_SIZE);
    this->ptr.size = this->IDT_TABLE_SIZE - 1; // TODO - sizeof the table
    this->ptr.base = this->table;

    this->set_all_gates();

    load_interrupt_descriptor_table(&this->ptr);
}
