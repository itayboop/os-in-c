#include "../Headers/idt.hpp"
#include "../Headers/utils.hpp"
#include <stdint.h>

void exc_divide_by_zero()
{
    printf("Divide by zero!\n");
}

void exc_debug()
{
    printf("Debug!\n");
}

void exc_nmi()
{
    printf("Non maskable interrupt!\n");
}

void exc_brp()
{
    printf("Breakpoint!\n");
}

void exc_overflow()
{
    printf("Overflow!\n");
}

void exc_bound()
{
    printf("Bound range exceeded.\n");
}

void exc_invopcode()
{
    printf("Invalid opcode.\n");
}

void exc_device_not_avail()
{
    printf("Device not available.\n");
}

void exc_double_fault()
{
    printf("Double fault, halting.\n");
    while(1);
}

void exc_coproc()
{
    printf("Coprocessor fault, halting.\n");
    while(1);
}

void exc_invtss()
{
    printf("TSS invalid.\n");
}

void exc_segment_not_present()
{
    printf("Segment not present.\n");
}

void exc_ssf()
{
    printf("Stacksegment faulted.\n");
}

void exc_gpf()
{
    printf("General protection fault.\n");
}

void exc_pf()
{
    printf("Page fault.\n");
}

void exc_reserved()
{
    printf("This shouldn't happen. Halted.\n");
    while(1);
}

void exceptions_init()
{
    printf("Installing exceptions handlers\n");
    idt_register_interrupt(0, (uint32_t)exc_divide_by_zero);
    idt_register_interrupt(1, (uint32_t)exc_debug);
    idt_register_interrupt(2, (uint32_t)exc_nmi);
    idt_register_interrupt(3, (uint32_t)exc_brp);
    idt_register_interrupt(4, (uint32_t)exc_overflow);
    idt_register_interrupt(5, (uint32_t)exc_bound);
    idt_register_interrupt(6, (uint32_t)exc_invopcode);
    idt_register_interrupt(7, (uint32_t)exc_device_not_avail);
    idt_register_interrupt(8, (uint32_t)exc_double_fault);
    idt_register_interrupt(9, (uint32_t)exc_coproc);
    idt_register_interrupt(10, (uint32_t)exc_invtss);
    idt_register_interrupt(11, (uint32_t)exc_segment_not_present);
    idt_register_interrupt(12, (uint32_t)exc_ssf);
    idt_register_interrupt(13, (uint32_t)exc_gpf);
    idt_register_interrupt(14, (uint32_t)exc_pf);
    idt_register_interrupt(15, (uint32_t)exc_reserved);
    return;
}