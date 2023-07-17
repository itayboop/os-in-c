#include <stdint.h>

#include "interrupts.hpp"
#include "utils.hpp"
#include "idt.hpp"

void exc_divide_by_zero(Registers& Registers)
{
	printf("Divide by zero at %x\n", Registers.rip);
	while(1);
}

void exc_debug(Registers& Registers)
{
	printf("Debug!\n");
	while (1);
}

void exc_non_maskable_int(Registers& Registers)
{
	printf("Non maskable interrupt!\n");
	while (1);
}

void exc_breakpoint(Registers& Registers)
{
	printf("Breakpoint at %x\n", Registers.rip);
	// TODO: add input check for enter in order to continue.
}

void exc_overflow(Registers& Registers)
{
	printf("Overflow!\n");
	while (1);
}

void exc_bound_range(Registers& Registers)
{
	printf("Bound range exceeded.\n");
	while (1);
}

void exc_invopcode(Registers& Registers)
{
	printf("Invalid opcode at %x\n", Registers.rip);
	while(1);
}

void exc_device_unavailable(Registers& Registers)
{
	printf("Device not available.\n");
	while (1);
}

void exc_double_fault(Registers& Registers)
{
	printf("Double fault, halting.\n");
	while(1);
}

void exc_invtss(Registers& Registers)
{
	printf("TSS invalid.\n");
	while (1);
}

void exc_segment_not_present(Registers& Registers)
{
	printf("Segment not present.\n");
	while (1);
}

void exc_stack_segment_fault(Registers& Registers)
{
	printf("Stacksegment faulted.\n");
	while (1);
}

void exc_gpf(Registers& Registers)
{
	printf("General protection fault at %x.\n", Registers.rip);
	while (1);
}

void exc_pf(Registers& Registers)
{
	printf("Page fault.\n");
	while (1);
}

void exc_kernel_fpu(Registers& Registers)
{
	printf("Kernel FPU error.\n");
	while (1);
}

void exc_align_check(Registers& Registers)
{
	printf("Align check error.\n");
	while (1);
}

void exc_machine_check(Registers& Registers)
{
	printf("Machine check exception.\n");
	while (1);
}

void exc_xm(Registers& Registers)
{
	printf("SIMD FP.\n");
	while (1);
}

void exc_virtualization(Registers& Registers)
{
	printf("Kernel virtualization exception.\n");
	while(1);
}

void register_all_interrupt_handlers()
{
	register_interrupt_handler(InterruptCode::DIV_BY_ZERO, exc_divide_by_zero);
	register_interrupt_handler(InterruptCode::DEBUG, exc_debug);
	register_interrupt_handler(InterruptCode::NON_MASKABLE_INT, exc_non_maskable_int);
	register_interrupt_handler(InterruptCode::BREAKPOINT, exc_breakpoint);
	register_interrupt_handler(InterruptCode::OVERFLOW, exc_overflow);
	register_interrupt_handler(InterruptCode::BOUND_RANGE, exc_bound_range);
	register_interrupt_handler(InterruptCode::INV_OPCODE, exc_invopcode);
	register_interrupt_handler(InterruptCode::DEVICE_UNAVAILABLE, exc_device_unavailable);
	register_interrupt_handler(InterruptCode::DOUBLE_FAULT, exc_double_fault);
	register_interrupt_handler(InterruptCode::INV_TSS, exc_invtss);
	register_interrupt_handler(InterruptCode::NOT_PRESENT, exc_segment_not_present);
	register_interrupt_handler(InterruptCode::STACK_SEGMANT_FAULT, exc_stack_segment_fault);
	register_interrupt_handler(InterruptCode::GENRAL_PROTECTION_FAULT, exc_gpf);
	register_interrupt_handler(InterruptCode::PAGE_FAULT, exc_pf);
	register_interrupt_handler(InterruptCode::KERNEL_FPU, exc_kernel_fpu);
	register_interrupt_handler(InterruptCode::ALIGN_CHECK, exc_align_check);
	register_interrupt_handler(InterruptCode::MACHINE_CHECK, exc_machine_check);
	register_interrupt_handler(InterruptCode::SIMF_FP, exc_xm);
	register_interrupt_handler(InterruptCode::VIRTUALIZATION, exc_virtualization);
}
