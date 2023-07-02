#include <stdint.h>

#include "../Headers/interrupts.hpp"
#include "../Headers/utils.hpp"

void exc_divide_by_zero() {
    printf("Divide by zero!\n");
    while(1) {};
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
    while(1) {};
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
    register_interrupt_handler(EXC_DIV_BY_ZERO, exc_divide_by_zero);
    register_interrupt_handler(EXC_DEBUG, exc_debug);
    register_interrupt_handler(EXC_NMI, exc_nmi);
    register_interrupt_handler(EXC_BP, exc_bp);
    register_interrupt_handler(EXC_OVERFLOW, exc_overflow);
    register_interrupt_handler(EXC_BR, exc_bound_range);
    register_interrupt_handler(EXC_INV_OPCODE, exc_invopcode);
    register_interrupt_handler(EXC_DU, exc_device_not_avail);
    register_interrupt_handler(EXC_DB_FAULT, exc_double_fault);
    register_interrupt_handler(EXC_INV_TSS, exc_invtss);
    register_interrupt_handler(EXC_NOT_PRESENT, exc_segment_not_present);
    register_interrupt_handler(EXC_SSF, exc_ssf);
    register_interrupt_handler(EXC_GP, exc_gpf);
    register_interrupt_handler(EXC_PF, exc_pf);
    register_interrupt_handler(EXC_PRESERVED, exc_reserved);
}