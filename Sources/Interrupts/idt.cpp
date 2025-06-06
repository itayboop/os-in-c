#include <stdint.h>

#include "../../Headers/Interrupts/idt.hpp"
#include "../../Headers/Utils/Functions/MemoryUtils.hpp"
#include "../../Headers/Utils/Functions/PrintUtils.hpp"

isr_t interrupt_handlers[256] __attribute__((aligned(16)));

registers_t *isr_handler(registers_t *registers)
{
    if (interrupt_handlers[registers->interrupt_number] == 0)
    {
        PrintUtils::printk("no iv for interrupt\n");
        while (1);
    } else
    {
        interrupt_handlers[registers->interrupt_number](registers);
    }

    return registers;
}

void IDT::idt_set_gate(uint8_t entry_number, uintptr_t funcall)
{
    idt_entry_64_t *entry = &this->idt[entry_number];

    entry->offset_high = (funcall >> 32) & 0xFFFFFFFF;
    entry->offset_mid = (funcall >> 16) & 0xFFFF;
    entry->offset_low = funcall & 0xFFFF;
    entry->type_attributes = 0xEF;
    entry->ist_index = 0;
    entry->selector = 8; // CODE descriptor, see gdt64.code
}

void IDT::register_interrupt_handler(uint8_t interrupt_number, isr_t handler_func)
{
    interrupt_handlers[interrupt_number] = handler_func;
}

void IDT::initialize_idt()
{
    MemoryUtils::memset(this->idt, 0, sizeof(this->idt));
    MemoryUtils::memset(interrupt_handlers, 0, sizeof(interrupt_handlers));

    this->idt_ptr.limit = (sizeof(this->idt)) - 1;
    this->idt_ptr.base = (uintptr_t) &this->idt;

    // GENERAL CPU INTERRUPTS
    this->idt_set_gate(0, (uintptr_t) isr0);
    this->idt_set_gate(1, (uintptr_t) isr1);
    this->idt_set_gate(2, (uintptr_t) isr2);
    this->idt_set_gate(3, (uintptr_t) isr3);
    this->idt_set_gate(4, (uintptr_t) isr4);
    this->idt_set_gate(5, (uintptr_t) isr5);
    this->idt_set_gate(6, (uintptr_t) isr6);
    this->idt_set_gate(7, (uintptr_t) isr7);
    this->idt_set_gate(8, (uintptr_t) isr8);
    this->idt_set_gate(9, (uintptr_t) isr9);
    this->idt_set_gate(10, (uintptr_t) isr10);
    this->idt_set_gate(11, (uintptr_t) isr11);
    this->idt_set_gate(12, (uintptr_t) isr12);
    this->idt_set_gate(13, (uintptr_t) isr13);
    this->idt_set_gate(14, (uintptr_t) isr14);
    this->idt_set_gate(15, (uintptr_t) isr15);
    this->idt_set_gate(16, (uintptr_t) isr16);
    this->idt_set_gate(17, (uintptr_t) isr17);
    this->idt_set_gate(18, (uintptr_t) isr18);
    this->idt_set_gate(19, (uintptr_t) isr19);
    this->idt_set_gate(20, (uintptr_t) isr20);
    this->idt_set_gate(21, (uintptr_t) isr21);
    this->idt_set_gate(22, (uintptr_t) isr22);
    this->idt_set_gate(23, (uintptr_t) isr23);
    this->idt_set_gate(24, (uintptr_t) isr24);
    this->idt_set_gate(25, (uintptr_t) isr25);
    this->idt_set_gate(26, (uintptr_t) isr26);
    this->idt_set_gate(27, (uintptr_t) isr27);
    this->idt_set_gate(28, (uintptr_t) isr28);
    this->idt_set_gate(29, (uintptr_t) isr29);
    this->idt_set_gate(30, (uintptr_t) isr30);
    this->idt_set_gate(31, (uintptr_t) isr31);
    this->idt_set_gate(32, (uintptr_t) isr32);
    this->idt_set_gate(33, (uintptr_t) isr33);
    this->idt_set_gate(34, (uintptr_t) isr34);
    this->idt_set_gate(35, (uintptr_t) isr35);
    this->idt_set_gate(36, (uintptr_t) isr36);
    this->idt_set_gate(37, (uintptr_t) isr37);
    this->idt_set_gate(38, (uintptr_t) isr38);
    this->idt_set_gate(39, (uintptr_t) isr39);
    this->idt_set_gate(40, (uintptr_t) isr40);
    this->idt_set_gate(41, (uintptr_t) isr41);
    this->idt_set_gate(42, (uintptr_t) isr42);
    this->idt_set_gate(43, (uintptr_t) isr43);
    this->idt_set_gate(44, (uintptr_t) isr44);
    this->idt_set_gate(45, (uintptr_t) isr45);
    this->idt_set_gate(46, (uintptr_t) isr46);
    this->idt_set_gate(47, (uintptr_t) isr47);

    load_idt(&this->idt_ptr);
}
