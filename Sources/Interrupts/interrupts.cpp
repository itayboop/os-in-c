#include "../../Headers/Interrupts/interrupts.hpp"
#include "../../Headers/Utils/Functions/PrintUtils.hpp"

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


void exc_divide_by_zero(registers_t *registers)
{
    PrintUtils::printk("Divide by zero at %x\n", registers->rip);
    while (1);
}

void exc_debug(registers_t *registers)
{
    PrintUtils::printk("Debug!\n");
    while (1);
}

void exc_nmi(registers_t *registers)
{
    PrintUtils::printk("Non maskable interrupt!\n");
    while (1);
}

void exc_bp(registers_t *registers)
{
    PrintUtils::printk("Breakpoint at %x\n", registers->rip);
    while (1);
}

void exc_overflow(registers_t *registers)
{
    PrintUtils::printk("Overflow!\n");
    while (1);
}

void exc_bound_range(registers_t *registers)
{
    PrintUtils::printk("Bound range exceeded.\n");
    while (1);
}

void exc_invopcode(registers_t *registers)
{
    PrintUtils::printk("Invalid opcode at %x\n", registers->rip);
    while (1);
}

void exc_device_not_avail(registers_t *registers)
{
    PrintUtils::printk("Device not available.\n");
    while (1);
}

void exc_double_fault(registers_t *registers)
{
    PrintUtils::printk("Double fault, halting.\n");
    while (1);
}

void exc_invtss(registers_t *registers)
{
    PrintUtils::printk("TSS invalid.\n");
    while (1);
}

void exc_segment_not_present(registers_t *registers)
{
    PrintUtils::printk("Segment not present.\n");
    while (1);
}

void exc_ssf(registers_t *registers)
{
    PrintUtils::printk("Stacksegment faulted.\n");
    while (1);
}

void exc_gpf(registers_t *registers)
{
    PrintUtils::printk("General protection fault at %x.\n", registers->rip);
    while (1);
}

void exc_pf(registers_t *registers)
{
    PrintUtils::printk("Page fault.\n");
    while (1);
}

void exc_kernel_fpu(registers_t *registers)
{
    PrintUtils::printk("Kernel FPU error.\n");
    while (1);
}

void exc_align_check(registers_t *registers)
{
    PrintUtils::printk("Align check error.\n");
    while (1);
}

void exc_machine_check(registers_t *registers)
{
    PrintUtils::printk("Machine check exception.\n");
    while (1);
}

void exc_xm(registers_t *registers)
{
    PrintUtils::printk("SIMD FP.\n");
    while (1);
}

void exc_virtualization(registers_t *registers)
{
    PrintUtils::printk("Kernel virtualization exception.\n");
    while (1);
}

void register_all_interrupt_handlers()
{
    register_interrupt_handler(static_cast<uint8_t>(InterruptVector::DIVIDE_BY_ZERO), exc_divide_by_zero);
    register_interrupt_handler(static_cast<uint8_t>(InterruptVector::DEBUG), exc_debug);
    register_interrupt_handler(static_cast<uint8_t>(InterruptVector::NON_MASKABLE_INTERRUPT), exc_nmi);
    register_interrupt_handler(static_cast<uint8_t>(InterruptVector::BREAKPOINT), exc_bp);
    register_interrupt_handler(static_cast<uint8_t>(InterruptVector::OVERFLOW), exc_overflow);
    register_interrupt_handler(static_cast<uint8_t>(InterruptVector::BOUND_RANGE_EXCEEDED), exc_bound_range);
    register_interrupt_handler(static_cast<uint8_t>(InterruptVector::INVALID_OPCODE), exc_invopcode);
    register_interrupt_handler(static_cast<uint8_t>(InterruptVector::DEVICE_NOT_AVAILABLE), exc_device_not_avail);
    register_interrupt_handler(static_cast<uint8_t>(InterruptVector::DOUBLE_FAULT), exc_double_fault);
    register_interrupt_handler(static_cast<uint8_t>(InterruptVector::INVALID_TSS), exc_invtss);
    register_interrupt_handler(static_cast<uint8_t>(InterruptVector::SEGMENT_NOT_PRESENT), exc_segment_not_present);
    register_interrupt_handler(static_cast<uint8_t>(InterruptVector::STACK_SEGMENT_FAULT), exc_ssf);
    register_interrupt_handler(static_cast<uint8_t>(InterruptVector::GENERAL_PROTECTION_FAULT), exc_gpf);
    register_interrupt_handler(static_cast<uint8_t>(InterruptVector::PAGE_FAULT), exc_pf);
    register_interrupt_handler(static_cast<uint8_t>(InterruptVector::KERNEL_FPU_EXCEPTION), exc_kernel_fpu);
    register_interrupt_handler(static_cast<uint8_t>(InterruptVector::ALIGNMENT_CHECK), exc_align_check);
    register_interrupt_handler(static_cast<uint8_t>(InterruptVector::MACHINE_CHECK), exc_machine_check);
    register_interrupt_handler(static_cast<uint8_t>(InterruptVector::SIMD_FP_EXCEPTION), exc_xm);
    register_interrupt_handler(static_cast<uint8_t>(InterruptVector::VIRTUALIZATION_EXCEPTION), exc_virtualization);

}