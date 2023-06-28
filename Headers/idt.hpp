#pragma once

#include <stdint.h>

struct idt_entry_64 {
    uint16_t offset_low;       // offset bits 0..15
    uint16_t selector;       // a code segment selector in GDT
    struct {
        uint16_t ist : 3; // interrupt stack table
        uint16_t r0 : 1;
        uint16_t r1 : 1;
        uint16_t r2 : 3;
        uint16_t type : 4; // trap or interrupt
        uint16_t r3 : 1;
        uint16_t dpl : 2; // descriptor priviledge level
        uint16_t p : 1;   // segment present flag
    } __attribute__((packed)) flags;
    uint16_t offset_mid;       // offset bits 16..31
    uint32_t offset_high;       // offset bits 32..63
    uint32_t reserved;           // reserved
} __attribute__((packed));
typedef struct idt_entry_64 idt_entry_64;

struct idt_64_pointer {
    uint16_t limit;
    uintptr_t base;
} __attribute__((packed));
typedef struct idt_64_pointer idt_64_pointer;

typedef struct registers_t
{
    uint64_t r15, r14, r13, r12, r11, r10, r9, r8, rbp, rcx, rbx;
    uint64_t rdx, rsi, rdi;
    uint64_t es, ds, fs, rax;
    uint64_t type, ecode;
    uint64_t rip, cs, rflags, uesp, ss;
} registers_t;


// create a new type isr
typedef void (*isr)();

void initialize_interrupts();
void register_interrupt_handler(uint8_t interrupt_id, isr handler_func);

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
