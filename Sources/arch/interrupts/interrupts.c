#include <stdint.h>

#include "interrupts.h"
#include "utils.h"

void exc_divide_by_zero(registers_t* registers)
{
	printf("Divide by zero at %x\n", registers->rip);
	while(1);
	// TODO: remove hanging and write a better resolve.
}

void exc_debug(registers_t* registers)
{
	printf("Debug!\n");
	while (1);
}

void exc_nmi(registers_t* registers)
{
	printf("Non maskable interrupt!\n");
	while (1);
}

void exc_bp(registers_t* registers)
{
	printf("Breakpoint at %x\n", registers->rip);
	// TODO: add input check for enter in order to continue.
}

void exc_overflow(registers_t* registers)
{
	printf("Overflow!\n");
	while (1);
}

void exc_bound_range(registers_t* registers)
{
	printf("Bound range exceeded.\n");
	while (1);
}

void exc_invopcode(registers_t* registers)
{
	printf("Invalid opcode at %x\n", registers->rip);
	while(1);
}

void exc_device_not_avail(registers_t* registers)
{
	printf("Device not available.\n");
	while (1);
}

void exc_double_fault(registers_t* registers)
{
	printf("Double fault, halting.\n");
	while(1);
}

void exc_invtss(registers_t* registers)
{
	printf("TSS invalid.\n");
	while (1);
}

void exc_segment_not_present(registers_t* registers)
{
	printf("Segment not present.\n");
	while (1);
}

void exc_ssf(registers_t* registers)
{
	printf("Stacksegment faulted.\n");
	while (1);
}

void exc_gpf(registers_t* registers)
{
	printf("General protection fault at %x.\n", registers->rip);
	while (1);
}

void exc_pf(registers_t* registers)
{
	printf("Page fault.\n");
	while (1);
}

void exc_kernel_fpu(registers_t* registers)
{
	printf("Kernel FPU error.\n");
	while (1);
}

void exc_align_check(registers_t* registers)
{
	printf("Align check error.\n");
	while (1);
}

void exc_machine_check(registers_t* registers)
{
	printf("Machine check exception.\n");
	while (1);
}

void exc_xm(registers_t* registers)
{
	printf("SIMD FP.\n");
	while (1);
}

void exc_virtualization(registers_t* registers)
{
	printf("Kernel virtualization exception.\n");
	while(1);
}

void register_all_interrupt_handlers()
{
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
	register_interrupt_handler(EXC_MF, exc_kernel_fpu);
	register_interrupt_handler(EXC_AC, exc_align_check);
	register_interrupt_handler(EXC_MC, exc_machine_check);
	register_interrupt_handler(EXC_XM, exc_xm);
	register_interrupt_handler(EXC_VE, exc_virtualization);
}
