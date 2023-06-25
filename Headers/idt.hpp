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
typedef void (*isr)(uintptr_t error_code, registers_t *);

void initialize_interrupts();
void register_interrupt_handler(uint8_t interrupt_id, isr handler_func);

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();
extern void isr32();
extern void isr33();
extern void isr34();
extern void isr35();
extern void isr36();
extern void isr37();
extern void isr38();
extern void isr39();
extern void isr40();
extern void isr41();
extern void isr42();
extern void isr43();
extern void isr44();
extern void isr45();
extern void isr46();
extern void isr47();
