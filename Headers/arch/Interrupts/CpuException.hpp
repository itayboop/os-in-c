#pragma once

#include "InterruptSource.hpp"
#include "InterruptsDescriptorTable.hpp"
#include "InterruptHandlersGenerator/InterruptHandlersGenerator.hpp"

class CpuExceptions final : public InterruptSource
{
public:
    void register_handlers(InterruptDescriptorTable &idt) override
    {
        idt.set_gate(0, (uintptr_t) isr0);
        idt.set_gate(1, (uintptr_t) isr1);
        idt.set_gate(2, (uintptr_t) isr2);
        idt.set_gate(3, (uintptr_t) isr3);
        idt.set_gate(4, (uintptr_t) isr4);
        idt.set_gate(5, (uintptr_t) isr5);
        idt.set_gate(6, (uintptr_t) isr6);
        idt.set_gate(7, (uintptr_t) isr7);
        idt.set_gate(8, (uintptr_t) isr8);
        idt.set_gate(9, (uintptr_t) isr9);
        idt.set_gate(10, (uintptr_t) isr10);
        idt.set_gate(11, (uintptr_t) isr11);
        idt.set_gate(12, (uintptr_t) isr12);
        idt.set_gate(13, (uintptr_t) isr13);
        idt.set_gate(14, (uintptr_t) isr14);
        idt.set_gate(15, (uintptr_t) isr15);
        idt.set_gate(16, (uintptr_t) isr16);
        idt.set_gate(17, (uintptr_t) isr17);
        idt.set_gate(18, (uintptr_t) isr18);
        idt.set_gate(19, (uintptr_t) isr19);
        idt.set_gate(20, (uintptr_t) isr20);
        idt.set_gate(21, (uintptr_t) isr21);
        idt.set_gate(22, (uintptr_t) isr22);
        idt.set_gate(23, (uintptr_t) isr23);
        idt.set_gate(24, (uintptr_t) isr24);
        idt.set_gate(25, (uintptr_t) isr25);
        idt.set_gate(26, (uintptr_t) isr26);
        idt.set_gate(27, (uintptr_t) isr27);
        idt.set_gate(28, (uintptr_t) isr28);
        idt.set_gate(29, (uintptr_t) isr29);
        idt.set_gate(30, (uintptr_t) isr30);
        idt.set_gate(31, (uintptr_t) isr31);
        idt.set_gate(32, (uintptr_t) isr32);
        idt.set_gate(33, (uintptr_t) isr33);
        idt.set_gate(34, (uintptr_t) isr34);
        idt.set_gate(35, (uintptr_t) isr35);
        idt.set_gate(36, (uintptr_t) isr36);
        idt.set_gate(37, (uintptr_t) isr37);
        idt.set_gate(38, (uintptr_t) isr38);
        idt.set_gate(39, (uintptr_t) isr39);
        idt.set_gate(40, (uintptr_t) isr40);
        idt.set_gate(41, (uintptr_t) isr41);
        idt.set_gate(42, (uintptr_t) isr42);
        idt.set_gate(43, (uintptr_t) isr43);
        idt.set_gate(44, (uintptr_t) isr44);
        idt.set_gate(45, (uintptr_t) isr45);
        idt.set_gate(46, (uintptr_t) isr46);
        idt.set_gate(47, (uintptr_t) isr47);
    }
};