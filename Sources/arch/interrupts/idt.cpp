#include <stdint.h>

#include "interrupts.hpp"
#include "utils.hpp"
#include "idt.hpp"

isr_t interrupt_handlers[256] __attribute__((aligned(16)));
idt_64_pointer_t idt_ptr __attribute__((aligned(16)));
idt_entry_64_t idt[256] __attribute__((aligned(16)));

extern "C" void load_idt(idt_64_pointer_t* ptr);

void register_interrupt_handler(uint8_t interrupt_number, isr_t handler_func)
{
    interrupt_handlers[interrupt_number] = handler_func;
}

extern "C" void isr_handler(registers_t* registers)
{
    if (interrupt_handlers[registers->interrupt_number] == 0)
    {
        printf("no iv for interrupt");
        while (1);
    }
    else
    {
        interrupt_handlers[registers->interrupt_number](registers);
    }
}

void idt_set_gate(uint8_t entry_number, uintptr_t funcall)
{
    idt_entry_64_t* entry = &idt[entry_number];

    entry->offset_high = (funcall >> 32) & 0xFFFFFFFF;
    entry->offset_mid = (funcall >> 16) & 0xFFFF;
    entry->offset_low = funcall & 0xFFFF;
    entry->type_attributes = 0xEF;
    entry->ist_index = 0;
    entry->selector = 8; // CODE descriptor, see gdt64.code
}

void initialize_idt()
{
    memset(idt, 0, sizeof(idt));
    memset(interrupt_handlers, 0, sizeof(interrupt_handlers));

    idt_ptr.limit = (sizeof(idt)) - 1;
    idt_ptr.base = (uintptr_t)&idt;

    // GENERAL CPU INTERRUPTS
    idt_set_gate(0, (uintptr_t)isr0);
    idt_set_gate(1, (uintptr_t)isr1);
    idt_set_gate(2, (uintptr_t)isr2);
    idt_set_gate(3, (uintptr_t)isr3);
    idt_set_gate(4, (uintptr_t)isr4);
    idt_set_gate(5, (uintptr_t)isr5);
    idt_set_gate(6, (uintptr_t)isr6);
    idt_set_gate(7, (uintptr_t)isr7);
    idt_set_gate(8, (uintptr_t)isr8);
    idt_set_gate(9, (uintptr_t)isr9);
    idt_set_gate(10, (uintptr_t)isr10);
    idt_set_gate(11, (uintptr_t)isr11);
    idt_set_gate(12, (uintptr_t)isr12);
    idt_set_gate(13, (uintptr_t)isr13);
    idt_set_gate(14, (uintptr_t)isr14);
    idt_set_gate(15, (uintptr_t)isr15);
    idt_set_gate(16, (uintptr_t)isr16);
    idt_set_gate(17, (uintptr_t)isr17);
    idt_set_gate(18, (uintptr_t)isr18);
    idt_set_gate(19, (uintptr_t)isr19);
    idt_set_gate(20, (uintptr_t)isr20);
    idt_set_gate(21, (uintptr_t)isr21);
    idt_set_gate(22, (uintptr_t)isr22);
    idt_set_gate(23, (uintptr_t)isr23);
    idt_set_gate(24, (uintptr_t)isr24);
    idt_set_gate(25, (uintptr_t)isr25);
    idt_set_gate(26, (uintptr_t)isr26);
    idt_set_gate(27, (uintptr_t)isr27);
    idt_set_gate(28, (uintptr_t)isr28);
    idt_set_gate(29, (uintptr_t)isr29);
    idt_set_gate(30, (uintptr_t)isr30);
    idt_set_gate(31, (uintptr_t)isr31);
    idt_set_gate(32, (uintptr_t)isr32);
    idt_set_gate(33, (uintptr_t)isr33);
    idt_set_gate(34, (uintptr_t)isr34);
    idt_set_gate(35, (uintptr_t)isr35);
    idt_set_gate(36, (uintptr_t)isr36);
    idt_set_gate(37, (uintptr_t)isr37);
    idt_set_gate(38, (uintptr_t)isr38);
    idt_set_gate(39, (uintptr_t)isr39);
    idt_set_gate(40, (uintptr_t)isr40);
    idt_set_gate(41, (uintptr_t)isr41);
    idt_set_gate(42, (uintptr_t)isr42);
    idt_set_gate(43, (uintptr_t)isr43);
    idt_set_gate(44, (uintptr_t)isr44);
    idt_set_gate(45, (uintptr_t)isr45);
    idt_set_gate(46, (uintptr_t)isr46);
    idt_set_gate(47, (uintptr_t)isr47);

    load_idt(&idt_ptr);
}
