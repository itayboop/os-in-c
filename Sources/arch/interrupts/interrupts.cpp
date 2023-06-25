#include <stdint.h>

#include "../Headers/interrupts.hpp"
#include "../Headers/utils.hpp"

void exc_divide_by_zero() {
    printf("Divide by zero!\n");
}

void exc_debug() {
    printf("Debug!\n");
}

void exc_nmi() {
    printf("Non maskable interrupt!\n");
}

void exc_bp() {
    printf("Breakpoint!\n");
}

void exc_overflow() {
    printf("Overflow!\n");
}

void exc_bound_range() {
    printf("Bound range exceeded.\n");
}

void exc_invopcode() {
    printf("Invalid opcode.\n");
}

void exc_device_not_avail() {
    printf("Device not available.\n");
}

void exc_double_fault() {
    printf("Double fault, halting.\n");
    while(1);
}

void exc_invtss() {
    printf("TSS invalid.\n");
}

void exc_segment_not_present() {
    printf("Segment not present.\n");
}

void exc_ssf() {
    printf("Stacksegment faulted.\n");
}

void exc_gpf() {
    printf("General protection fault.\n");
}

void exc_pf() {
    printf("Page fault.\n");
}

void exc_reserved() {
    printf("This shouldn't happen. Halted.\n");
    while(1);
}

void register_all_interrupt_handlers() {
    printf("Installing exceptions handlers...\n");

    register_interrupt_handler(EXC_DIV_BY_ZERO, (isr)exc_divide_by_zero);
    register_interrupt_handler(EXC_DEBUG, (isr)exc_debug);
    register_interrupt_handler(EXC_NMI, (isr)exc_nmi);
    register_interrupt_handler(EXC_BP, (isr)exc_bp);
    register_interrupt_handler(EXC_OVERFLOW, (isr)exc_overflow);
    register_interrupt_handler(EXC_BR, (isr)exc_bound_range);
    register_interrupt_handler(EXC_INV_OPCODE, (isr)exc_invopcode);
    register_interrupt_handler(EXC_DU, (isr)exc_device_not_avail);
    register_interrupt_handler(EXC_DB_FAULT, (isr)exc_double_fault);
    register_interrupt_handler(EXC_INV_TSS, (isr)exc_invtss);
    register_interrupt_handler(EXC_NOT_PRESENT, (isr)exc_segment_not_present);
    register_interrupt_handler(EXC_SSF, (isr)exc_ssf);
    register_interrupt_handler(EXC_GP, (isr)exc_gpf);
    register_interrupt_handler(EXC_PF, (isr)exc_pf);
    register_interrupt_handler(EXC_PRESERVED, (isr)exc_reserved);

    printf("Done.\n");
}