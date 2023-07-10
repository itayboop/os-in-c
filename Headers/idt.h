#pragma once
#include <stdint.h>

typedef struct __attribute__((packed)) idt_entry_64_t
{
	uint16_t offset_low;	// offset bits 0..15
	uint16_t selector;	// a code segment selector in GDT
	uint8_t ist_index;
	uint8_t type_attributes;
	uint16_t offset_mid;	// offset bits 16..31
	uint32_t offset_high;	// offset bits 32..63
	uint32_t reserved;
} idt_entry_64_t;

typedef struct __attribute__((packed)) idt_64_pointer_t
{
	uint16_t limit;
	uintptr_t base;
} idt_64_pointer_t;

typedef struct __attribute__((packed)) registers_t
{
	uint64_t r15, r14, r13, r12, r11, r10, r9, r8;
	uint64_t rbp, rdi, rsi, rdx, rcx, rbx, rax;

	uint64_t interrupt_number, error_code;

	uint64_t rip, cs, rflags, rsp, ss;
} registers_t;

// create a new function type isr_t
typedef void (*isr_t)(registers_t* registers);

void initialize_idt();
void register_interrupt_handler(uint8_t interrupt_number, isr_t handler_func);

void isr0();
void isr1();
void isr2();
void isr3();
void isr4();
void isr5();
void isr6();
void isr7();
void isr8();
void isr9();
void isr10();
void isr11();
void isr12();
void isr13();
void isr14();
void isr15();
void isr16();
void isr17();
void isr18();
void isr19();
void isr20();
void isr21();
void isr22();
void isr23();
void isr24();
void isr25();
void isr26();
void isr27();
void isr28();
void isr29();
void isr30();
void isr31();
void isr32();
void isr33();
void isr34();
void isr35();
void isr36();
void isr37();
void isr38();
void isr39();
void isr40();
void isr41();
void isr42();
void isr43();
void isr44();
void isr45();
void isr46();
void isr47();
