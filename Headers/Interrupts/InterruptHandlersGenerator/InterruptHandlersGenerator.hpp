#pragma once

#include <stdint.h>

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

typedef struct __attribute__((packed)) isr_registers_s
{
    uint64_t r15, r14, r13, r12, r11, r10, r9, r8;
    uint64_t rbp, rdi, rsi, rdx, rcx, rbx, rax;

    uint64_t interrupt_number, error_code;

    uint64_t rip, cs, rflags, rsp, ss;
} isr_registers_t;

using isr_t = void(*)(isr_registers_t *registers);

extern "C" isr_registers_t *isr_handler(isr_registers_t *registers);

enum class InterruptVector : uint8_t
{
    DIVIDE_BY_ZERO             = 0,
    DEBUG                      = 1,
    NON_MASKABLE_INTERRUPT     = 2,
    BREAKPOINT                 = 3,
    OVERFLOW                   = 4,
    BOUND_RANGE_EXCEEDED       = 5,
    INVALID_OPCODE             = 6,
    DEVICE_NOT_AVAILABLE       = 7,
    DOUBLE_FAULT               = 8,
    INVALID_TSS                = 10,
    SEGMENT_NOT_PRESENT        = 11,
    STACK_SEGMENT_FAULT        = 12,
    GENERAL_PROTECTION_FAULT   = 13,
    PAGE_FAULT                 = 14,
    KERNEL_FPU_EXCEPTION       = 16,
    ALIGNMENT_CHECK            = 17,
    MACHINE_CHECK              = 18,
    SIMD_FP_EXCEPTION          = 19,
    VIRTUALIZATION_EXCEPTION   = 20,
};

class InterruptHandlersGenerator
{
private:
    void static exc_divide_by_zero(isr_registers_t *registers);
    void static exc_debug(isr_registers_t *registers);
    void static exc_nmi(isr_registers_t *registers);
    void static exc_bp(isr_registers_t *registers);
    void static exc_overflow(isr_registers_t *registers);
    void static exc_bound_range(isr_registers_t *registers);
    void static exc_invopcode(isr_registers_t *registers);
    void static exc_device_not_avail(isr_registers_t *registers);
    void static exc_double_fault(isr_registers_t *registers);
    void static exc_invtss(isr_registers_t *registers);
    void static exc_segment_not_present(isr_registers_t *registers);
    void static exc_ssf(isr_registers_t *registers);
    void static exc_gpf(isr_registers_t *registers);
    void static exc_pf(isr_registers_t *registers);
    void static exc_kernel_fpu(isr_registers_t *registers);
    void static exc_align_check(isr_registers_t *registers);
    void static exc_machine_check(isr_registers_t *registers);
    void static exc_xm(isr_registers_t *registers);
    void static exc_virtualization(isr_registers_t *registers);

    void register_interrupt_handler(uint8_t interrupt_number, isr_t handler_func);
    void register_all_interrupt_handlers();

public:
    void generate();
};