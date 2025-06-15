#include <stdint.h>

#include "../../Headers/Interrupts/idt.hpp"
#include "../../Headers/Utils/Functions/MemoryUtils.hpp"
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

isr_t interrupt_handlers[256] __attribute__((aligned(16)));

registers_t *isr_handler(registers_t *registers)
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

void IDT::set_gate(uint8_t entry_number, uintptr_t funcall)
{
    idt_entry_64_t *entry = &this->idt[entry_number];

    entry->offset_high = (funcall >> 32) & 0xFFFFFFFF;
    entry->offset_mid = (funcall >> 16) & 0xFFFF;
    entry->offset_low = funcall & 0xFFFF;
    entry->type_attributes = 0xEF;
    entry->ist_index = 0;
    entry->selector = 8; // CODE descriptor, see gdt64.code
}

void IDT::set_all_gates()
{
    this->set_gate(0, (uintptr_t) isr0);
    this->set_gate(1, (uintptr_t) isr1);
    this->set_gate(2, (uintptr_t) isr2);
    this->set_gate(3, (uintptr_t) isr3);
    this->set_gate(4, (uintptr_t) isr4);
    this->set_gate(5, (uintptr_t) isr5);
    this->set_gate(6, (uintptr_t) isr6);
    this->set_gate(7, (uintptr_t) isr7);
    this->set_gate(8, (uintptr_t) isr8);
    this->set_gate(9, (uintptr_t) isr9);
    this->set_gate(10, (uintptr_t) isr10);
    this->set_gate(11, (uintptr_t) isr11);
    this->set_gate(12, (uintptr_t) isr12);
    this->set_gate(13, (uintptr_t) isr13);
    this->set_gate(14, (uintptr_t) isr14);
    this->set_gate(15, (uintptr_t) isr15);
    this->set_gate(16, (uintptr_t) isr16);
    this->set_gate(17, (uintptr_t) isr17);
    this->set_gate(18, (uintptr_t) isr18);
    this->set_gate(19, (uintptr_t) isr19);
    this->set_gate(20, (uintptr_t) isr20);
    this->set_gate(21, (uintptr_t) isr21);
    this->set_gate(22, (uintptr_t) isr22);
    this->set_gate(23, (uintptr_t) isr23);
    this->set_gate(24, (uintptr_t) isr24);
    this->set_gate(25, (uintptr_t) isr25);
    this->set_gate(26, (uintptr_t) isr26);
    this->set_gate(27, (uintptr_t) isr27);
    this->set_gate(28, (uintptr_t) isr28);
    this->set_gate(29, (uintptr_t) isr29);
    this->set_gate(30, (uintptr_t) isr30);
    this->set_gate(31, (uintptr_t) isr31);
    this->set_gate(32, (uintptr_t) isr32);
    this->set_gate(33, (uintptr_t) isr33);
    this->set_gate(34, (uintptr_t) isr34);
    this->set_gate(35, (uintptr_t) isr35);
    this->set_gate(36, (uintptr_t) isr36);
    this->set_gate(37, (uintptr_t) isr37);
    this->set_gate(38, (uintptr_t) isr38);
    this->set_gate(39, (uintptr_t) isr39);
    this->set_gate(40, (uintptr_t) isr40);
    this->set_gate(41, (uintptr_t) isr41);
    this->set_gate(42, (uintptr_t) isr42);
    this->set_gate(43, (uintptr_t) isr43);
    this->set_gate(44, (uintptr_t) isr44);
    this->set_gate(45, (uintptr_t) isr45);
    this->set_gate(46, (uintptr_t) isr46);
    this->set_gate(47, (uintptr_t) isr47);
}

void IDT::register_interrupt_handler(uint8_t interrupt_number, isr_t handler_func)
{
    interrupt_handlers[interrupt_number] = handler_func;
}

void IDT::register_all_interrupt_handlers()
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

void IDT::initialize_idt()
{
    MemoryUtils::memset(interrupt_handlers, 0, sizeof(interrupt_handlers));
    this->register_all_interrupt_handlers();

    MemoryUtils::memset(this->idt, 0, sizeof(this->idt));
    this->idt_ptr.limit = (sizeof(this->idt)) - 1;
    this->idt_ptr.base = (uintptr_t) &this->idt;
    load_idt(&this->idt_ptr);

    this->set_all_gates();
}
