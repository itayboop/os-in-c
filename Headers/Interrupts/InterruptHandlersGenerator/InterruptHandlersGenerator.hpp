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

struct __attribute__((packed)) InterruptServiceRoutineRegisters
{
    uint64_t r15, r14, r13, r12, r11, r10, r9, r8;
    uint64_t rbp, rdi, rsi, rdx, rcx, rbx, rax;

    uint64_t interrupt_number, error_code;

    uint64_t rip, cs, rflags, rsp, ss;
};

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

public:
    static InterruptServiceRoutineRegisters * isr_handler(InterruptServiceRoutineRegisters *registers);
    void generate();
};