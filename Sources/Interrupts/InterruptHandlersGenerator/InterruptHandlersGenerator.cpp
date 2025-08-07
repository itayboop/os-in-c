#include "Utils/Functions/PrintUtils.hpp"
#include "Utils/Functions/MemoryUtils.hpp"
#include "Interrupts/InterruptHandlersGenerator/InterruptHandlersGenerator.hpp"

interrupt_service_routine_t interrupt_handlers[256] __attribute__((aligned(16)));

InterruptServiceRoutineRegisters * isr_handler_wrapper(InterruptServiceRoutineRegisters *registers)
{
    return InterruptHandlersGenerator::isr_handler(registers);
}

InterruptServiceRoutineRegisters * InterruptHandlersGenerator::isr_handler(InterruptServiceRoutineRegisters *registers)
{
    if (interrupt_handlers[registers->interrupt_number] == 0)
    {
        PrintUtils::printk("no iv for interrupt\n");
        while (1);
    } else
    {
        interrupt_handlers[registers->interrupt_number](*registers);
    }

    return registers;
}

InterruptHandlersGenerator::InterruptHandlersGenerator()
{
    this->generate();
}

void InterruptHandlersGenerator::exc_divide_by_zero(InterruptServiceRoutineRegisters &registers)
{
    PrintUtils::printk("Divide by zero at %x\n", registers.rip);
    while (1);
}

void InterruptHandlersGenerator::exc_debug(InterruptServiceRoutineRegisters &registers)
{
    PrintUtils::printk("Debug!\n");
    while (1);
}

void InterruptHandlersGenerator::exc_nmi(InterruptServiceRoutineRegisters &registers)
{
    PrintUtils::printk("Non maskable interrupt!\n");
    while (1);
}

void InterruptHandlersGenerator::exc_bp(InterruptServiceRoutineRegisters &registers)
{
    PrintUtils::printk("Breakpoint at %x\n", registers.rip);
    while (1);
}

void InterruptHandlersGenerator::exc_overflow(InterruptServiceRoutineRegisters &registers)
{
    PrintUtils::printk("Overflow!\n");
    while (1);
}

void InterruptHandlersGenerator::exc_bound_range(InterruptServiceRoutineRegisters &registers)
{
    PrintUtils::printk("Bound range exceeded.\n");
    while (1);
}

void InterruptHandlersGenerator::exc_invopcode(InterruptServiceRoutineRegisters &registers)
{
    PrintUtils::printk("Invalid opcode at %x\n", registers.rip);
    while (1);
}

void InterruptHandlersGenerator::exc_device_not_avail(InterruptServiceRoutineRegisters &registers)
{
    PrintUtils::printk("Device not available.\n");
    while (1);
}

void InterruptHandlersGenerator::exc_double_fault(InterruptServiceRoutineRegisters &registers)
{
    PrintUtils::printk("Double fault, halting.\n");
    while (1);
}

void InterruptHandlersGenerator::exc_invtss(InterruptServiceRoutineRegisters &registers)
{
    PrintUtils::printk("TSS invalid.\n");
    while (1);
}

void InterruptHandlersGenerator::exc_segment_not_present(InterruptServiceRoutineRegisters &registers)
{
    PrintUtils::printk("Segment not present.\n");
    while (1);
}

void InterruptHandlersGenerator::exc_ssf(InterruptServiceRoutineRegisters &registers)
{
    PrintUtils::printk("Stacksegment faulted.\n");
    while (1);
}

void InterruptHandlersGenerator::exc_gpf(InterruptServiceRoutineRegisters &registers)
{
    PrintUtils::printk("General protection fault at %x.\n", registers.rip);
    while (1);
}

void InterruptHandlersGenerator::exc_pf(InterruptServiceRoutineRegisters &registers)
{
    PrintUtils::printk("Page fault.\n");
    while (1);
}

void InterruptHandlersGenerator::exc_kernel_fpu(InterruptServiceRoutineRegisters &registers)
{
    PrintUtils::printk("Kernel FPU error.\n");
    while (1);
}

void InterruptHandlersGenerator::exc_align_check(InterruptServiceRoutineRegisters &registers)
{
    PrintUtils::printk("Align check error.\n");
    while (1);
}

void InterruptHandlersGenerator::exc_machine_check(InterruptServiceRoutineRegisters &registers)
{
    PrintUtils::printk("Machine check exception.\n");
    while (1);
}

void InterruptHandlersGenerator::exc_xm(InterruptServiceRoutineRegisters &registers)
{
    PrintUtils::printk("SIMD FP.\n");
    while (1);
}

void InterruptHandlersGenerator::exc_virtualization(InterruptServiceRoutineRegisters &registers)
{
    PrintUtils::printk("Kernel virtualization exception.\n");
    while (1);
}

void InterruptHandlersGenerator::register_interrupt_handler(InterruptVector interrupt_number, interrupt_service_routine_t handler_func)
{
    interrupt_handlers[static_cast<uint8_t>(interrupt_number)] = handler_func;
}

void InterruptHandlersGenerator::register_all_interrupt_handlers()
{
    this->register_interrupt_handler(InterruptVector::DIVIDE_BY_ZERO, exc_divide_by_zero);
    this->register_interrupt_handler(InterruptVector::DEBUG, exc_debug);
    this->register_interrupt_handler(InterruptVector::NON_MASKABLE_INTERRUPT, exc_nmi);
    this->register_interrupt_handler(InterruptVector::BREAKPOINT, exc_bp);
    this->register_interrupt_handler(InterruptVector::OVERFLOW, exc_overflow);
    this->register_interrupt_handler(InterruptVector::BOUND_RANGE_EXCEEDED, exc_bound_range);
    this->register_interrupt_handler(InterruptVector::INVALID_OPCODE, exc_invopcode);
    this->register_interrupt_handler(InterruptVector::DEVICE_NOT_AVAILABLE, exc_device_not_avail);
    this->register_interrupt_handler(InterruptVector::DOUBLE_FAULT, exc_double_fault);
    this->register_interrupt_handler(InterruptVector::INVALID_TSS, exc_invtss);
    this->register_interrupt_handler(InterruptVector::SEGMENT_NOT_PRESENT, exc_segment_not_present);
    this->register_interrupt_handler(InterruptVector::STACK_SEGMENT_FAULT, exc_ssf);
    this->register_interrupt_handler(InterruptVector::GENERAL_PROTECTION_FAULT, exc_gpf);
    this->register_interrupt_handler(InterruptVector::PAGE_FAULT, exc_pf);
    this->register_interrupt_handler(InterruptVector::KERNEL_FPU_EXCEPTION, exc_kernel_fpu);
    this->register_interrupt_handler(InterruptVector::ALIGNMENT_CHECK, exc_align_check);
    this->register_interrupt_handler(InterruptVector::MACHINE_CHECK, exc_machine_check);
    this->register_interrupt_handler(InterruptVector::SIMD_FP_EXCEPTION, exc_xm);
    this->register_interrupt_handler(InterruptVector::VIRTUALIZATION_EXCEPTION, exc_virtualization);
}

void InterruptHandlersGenerator::generate()
{
    MemoryUtils::memset(interrupt_handlers, 0, sizeof(interrupt_handlers));
    this->register_all_interrupt_handlers();
}
