#include "../../../Headers/Interrupts/InterruptHandlersGenerator/InterruptHandlersGenerator.hpp"
#include "../../../Headers/Utils/Functions/PrintUtils.hpp"
#include "../../../Headers/Utils/Functions/MemoryUtils.hpp"

isr_t interrupt_handlers[256] __attribute__((aligned(16)));

isr_registers_t *isr_handler(isr_registers_t *registers)
{
    if (interrupt_handlers[registers->interrupt_number] == 0)
    {
        PrintUtils::printk("no iv for interrupt\n");
        while (1);
    } else
    {
        interrupt_handlers[registers->interrupt_number](registers);
    }

    return registers;
}

void InterruptHandlersGenerator::exc_divide_by_zero(isr_registers_t *registers)
{
    PrintUtils::printk("Divide by zero at %x\n", registers->rip);
    while (1);
}

void InterruptHandlersGenerator::exc_debug(isr_registers_t *registers)
{
    PrintUtils::printk("Debug!\n");
    while (1);
}

void InterruptHandlersGenerator::exc_nmi(isr_registers_t *registers)
{
    PrintUtils::printk("Non maskable interrupt!\n");
    while (1);
}

void InterruptHandlersGenerator::exc_bp(isr_registers_t *registers)
{
    PrintUtils::printk("Breakpoint at %x\n", registers->rip);
    while (1);
}

void InterruptHandlersGenerator::exc_overflow(isr_registers_t *registers)
{
    PrintUtils::printk("Overflow!\n");
    while (1);
}

void InterruptHandlersGenerator::exc_bound_range(isr_registers_t *registers)
{
    PrintUtils::printk("Bound range exceeded.\n");
    while (1);
}

void InterruptHandlersGenerator::exc_invopcode(isr_registers_t *registers)
{
    PrintUtils::printk("Invalid opcode at %x\n", registers->rip);
    while (1);
}

void InterruptHandlersGenerator::exc_device_not_avail(isr_registers_t *registers)
{
    PrintUtils::printk("Device not available.\n");
    while (1);
}

void InterruptHandlersGenerator::exc_double_fault(isr_registers_t *registers)
{
    PrintUtils::printk("Double fault, halting.\n");
    while (1);
}

void InterruptHandlersGenerator::exc_invtss(isr_registers_t *registers)
{
    PrintUtils::printk("TSS invalid.\n");
    while (1);
}

void InterruptHandlersGenerator::exc_segment_not_present(isr_registers_t *registers)
{
    PrintUtils::printk("Segment not present.\n");
    while (1);
}

void InterruptHandlersGenerator::exc_ssf(isr_registers_t *registers)
{
    PrintUtils::printk("Stacksegment faulted.\n");
    while (1);
}

void InterruptHandlersGenerator::exc_gpf(isr_registers_t *registers)
{
    PrintUtils::printk("General protection fault at %x.\n", registers->rip);
    while (1);
}

void InterruptHandlersGenerator::exc_pf(isr_registers_t *registers)
{
    PrintUtils::printk("Page fault.\n");
    while (1);
}

void InterruptHandlersGenerator::exc_kernel_fpu(isr_registers_t *registers)
{
    PrintUtils::printk("Kernel FPU error.\n");
    while (1);
}

void InterruptHandlersGenerator::exc_align_check(isr_registers_t *registers)
{
    PrintUtils::printk("Align check error.\n");
    while (1);
}

void InterruptHandlersGenerator::exc_machine_check(isr_registers_t *registers)
{
    PrintUtils::printk("Machine check exception.\n");
    while (1);
}

void InterruptHandlersGenerator::exc_xm(isr_registers_t *registers)
{
    PrintUtils::printk("SIMD FP.\n");
    while (1);
}

void InterruptHandlersGenerator::exc_virtualization(isr_registers_t *registers)
{
    PrintUtils::printk("Kernel virtualization exception.\n");
    while (1);
}

void InterruptHandlersGenerator::register_interrupt_handler(uint8_t interrupt_number, isr_t handler_func)
{
    interrupt_handlers[interrupt_number] = handler_func;
}

void InterruptHandlersGenerator::register_all_interrupt_handlers()
{
    this->register_interrupt_handler(static_cast<uint8_t>(InterruptVector::DIVIDE_BY_ZERO), exc_divide_by_zero);
    this->register_interrupt_handler(static_cast<uint8_t>(InterruptVector::DEBUG), exc_debug);
    this->register_interrupt_handler(static_cast<uint8_t>(InterruptVector::NON_MASKABLE_INTERRUPT), exc_nmi);
    this->register_interrupt_handler(static_cast<uint8_t>(InterruptVector::BREAKPOINT), exc_bp);
    this->register_interrupt_handler(static_cast<uint8_t>(InterruptVector::OVERFLOW), exc_overflow);
    this->register_interrupt_handler(static_cast<uint8_t>(InterruptVector::BOUND_RANGE_EXCEEDED), exc_bound_range);
    this->register_interrupt_handler(static_cast<uint8_t>(InterruptVector::INVALID_OPCODE), exc_invopcode);
    this->register_interrupt_handler(static_cast<uint8_t>(InterruptVector::DEVICE_NOT_AVAILABLE), exc_device_not_avail);
    this->register_interrupt_handler(static_cast<uint8_t>(InterruptVector::DOUBLE_FAULT), exc_double_fault);
    this->register_interrupt_handler(static_cast<uint8_t>(InterruptVector::INVALID_TSS), exc_invtss);
    this->register_interrupt_handler(static_cast<uint8_t>(InterruptVector::SEGMENT_NOT_PRESENT), exc_segment_not_present);
    this->register_interrupt_handler(static_cast<uint8_t>(InterruptVector::STACK_SEGMENT_FAULT), exc_ssf);
    this->register_interrupt_handler(static_cast<uint8_t>(InterruptVector::GENERAL_PROTECTION_FAULT), exc_gpf);
    this->register_interrupt_handler(static_cast<uint8_t>(InterruptVector::PAGE_FAULT), exc_pf);
    this->register_interrupt_handler(static_cast<uint8_t>(InterruptVector::KERNEL_FPU_EXCEPTION), exc_kernel_fpu);
    this->register_interrupt_handler(static_cast<uint8_t>(InterruptVector::ALIGNMENT_CHECK), exc_align_check);
    this->register_interrupt_handler(static_cast<uint8_t>(InterruptVector::MACHINE_CHECK), exc_machine_check);
    this->register_interrupt_handler(static_cast<uint8_t>(InterruptVector::SIMD_FP_EXCEPTION), exc_xm);
    this->register_interrupt_handler(static_cast<uint8_t>(InterruptVector::VIRTUALIZATION_EXCEPTION), exc_virtualization);
}

void InterruptHandlersGenerator::generate()
{
    MemoryUtils::memset(interrupt_handlers, 0, sizeof(interrupt_handlers));
    this->register_all_interrupt_handlers();
}