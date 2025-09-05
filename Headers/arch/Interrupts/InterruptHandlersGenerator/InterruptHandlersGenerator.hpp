#pragma once

#include <stdint.h>
#include "macros.h"

extern "C" {
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
}

struct InterruptServiceRoutineRegisters
{
    uint64_t r15, r14, r13, r12, r11, r10, r9, r8;
    uint64_t rbp, rdi, rsi, rdx, rcx, rbx, rax;

    uint64_t interrupt_number, error_code;

    uint64_t rip, cs, rflags, rsp, ss;
} PACKED;

using interrupt_service_routine_t = void(*)(InterruptServiceRoutineRegisters &registers);

extern "C" InterruptServiceRoutineRegisters *isr_handler_wrapper(InterruptServiceRoutineRegisters *registers);

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
public:
    InterruptHandlersGenerator();

private:
    void static exc_divide_by_zero(InterruptServiceRoutineRegisters &registers);
    void static exc_debug(InterruptServiceRoutineRegisters &registers);
    void static exc_nmi(InterruptServiceRoutineRegisters &registers);
    void static exc_bp(InterruptServiceRoutineRegisters &registers);
    void static exc_overflow(InterruptServiceRoutineRegisters &registers);
    void static exc_bound_range(InterruptServiceRoutineRegisters &registers);
    void static exc_invopcode(InterruptServiceRoutineRegisters &registers);
    void static exc_device_not_avail(InterruptServiceRoutineRegisters &registers);
    void static exc_double_fault(InterruptServiceRoutineRegisters &registers);
    void static exc_invtss(InterruptServiceRoutineRegisters &registers);
    void static exc_segment_not_present(InterruptServiceRoutineRegisters &registers);
    void static exc_ssf(InterruptServiceRoutineRegisters &registers);
    void static exc_gpf(InterruptServiceRoutineRegisters &registers);
    void static exc_pf(InterruptServiceRoutineRegisters &registers);
    void static exc_kernel_fpu(InterruptServiceRoutineRegisters &registers);
    void static exc_align_check(InterruptServiceRoutineRegisters &registers);
    void static exc_machine_check(InterruptServiceRoutineRegisters &registers);
    void static exc_xm(InterruptServiceRoutineRegisters &registers);
    void static exc_virtualization(InterruptServiceRoutineRegisters &registers);

    void register_interrupt_handler(InterruptVector interrupt_number, interrupt_service_routine_t handler_func);
    void register_all_interrupt_handlers();

    void generate();

public:
    static InterruptServiceRoutineRegisters * isr_handler(InterruptServiceRoutineRegisters *registers);
};
