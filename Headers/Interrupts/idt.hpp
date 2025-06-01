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
    uint16_t limit;
    uintptr_t base;
} idt_64_pointer_t;

typedef struct __attribute__((packed)) registers_s
{
    uint64_t r15, r14, r13, r12, r11, r10, r9, r8;
    uint64_t rbp, rdi, rsi, rdx, rcx, rbx, rax;

    uint64_t interrupt_number, error_code;

    uint64_t rip, cs, rflags, rsp, ss;
} registers_t;

typedef void (*isr_t)(registers_t *registers);

extern "C" registers_t *isr_handler(registers_t *registers);

extern "C" void load_idt(idt_64_pointer_t *ptr);

void initialize_idt();

void register_interrupt_handler(uint8_t interrupt_number, isr_t handler_func);

extern "C" void isr0();
extern "C" void isr1();
extern "C" void isr2();
extern "C" void isr3();
extern "C" void isr4();
extern "C" void isr5();
extern "C" void isr6();
extern "C" void isr7();
extern "C" void isr8();
extern "C" void isr9();
extern "C" void isr10();
extern "C" void isr11();
extern "C" void isr12();
extern "C" void isr13();
extern "C" void isr14();
extern "C" void isr15();
extern "C" void isr16();
extern "C" void isr17();
extern "C" void isr18();
extern "C" void isr19();
extern "C" void isr20();
extern "C" void isr21();
extern "C" void isr22();
extern "C" void isr23();
extern "C" void isr24();
extern "C" void isr25();
extern "C" void isr26();
extern "C" void isr27();
extern "C" void isr28();
extern "C" void isr29();
extern "C" void isr30();
extern "C" void isr31();
extern "C" void isr32();
extern "C" void isr33();
extern "C" void isr34();
extern "C" void isr35();
extern "C" void isr36();
extern "C" void isr37();
extern "C" void isr38();
extern "C" void isr39();
extern "C" void isr40();
extern "C" void isr41();
extern "C" void isr42();
extern "C" void isr43();
extern "C" void isr44();
extern "C" void isr45();
extern "C" void isr46();
extern "C" void isr47();