#include "stdint.h"

#include "Utils/Vector.hpp"
#include "Utils/Macros.hpp"
#include "Utils/Functions/PrintUtils.hpp"
#include "Utils/Functions/MemoryUtils.hpp"
#include "Arch/InterruptServiceRoutine/InterruptServiceRoutineEntries.hpp"

void exc_divide_by_zero(ProcessorRegisterSet* isr_registers)
{
	PrintUtils::printk("Divide by zero at %x\n", isr_registers->rip);
	while (1);
}

void exc_debug(ProcessorRegisterSet* isr_registers)
{
	PrintUtils::printk("Debug!\n");
	while (1);
}

void exc_non_maskable_int(ProcessorRegisterSet* isr_registers)
{
	PrintUtils::printk("Non maskable interrupt!\n");
	while (1);
}

void exc_breakpoint(ProcessorRegisterSet* isr_registers)
{
	PrintUtils::printk("Breakpoint at %x\n", isr_registers->rip);
	while(1);
	// TODO: add input check for enter in order to continue.
}

void exc_overflow(ProcessorRegisterSet* isr_registers)
{
	PrintUtils::printk("Overflow!\n");
	while (1);
}

void exc_bound_range(ProcessorRegisterSet* isr_registers)
{
	PrintUtils::printk("Bound range exceeded.\n");
	while (1);
}

void exc_invopcode(ProcessorRegisterSet* isr_registers)
{
	PrintUtils::printk("Invalid opcode at %x\n", isr_registers->rip);
	while (1);
}

void exc_device_unavailable(ProcessorRegisterSet* isr_registers)
{
	PrintUtils::printk("Device not available.\n");
	while (1);
}

void exc_double_fault(ProcessorRegisterSet* isr_registers)
{
	PrintUtils::printk("Double fault, halting.\n");
	while (1);
}

void exc_invtss(ProcessorRegisterSet* isr_registers)
{
	PrintUtils::printk("TSS invalid.\n");
	while (1);
}

void exc_segment_not_present(ProcessorRegisterSet* isr_registers)
{
	PrintUtils::printk("Segment not present.\n");
	while (1);
}

void exc_stack_segment_fault(ProcessorRegisterSet* isr_registers)
{
	PrintUtils::printk("Stacksegment faulted.\n");
	while (1);
}

void exc_gpf(ProcessorRegisterSet* isr_registers)
{
	PrintUtils::printk("General protection fault at %x.\n", isr_registers->rip);
	while (1);
}

void exc_pf(ProcessorRegisterSet* isr_registers)
{
	PrintUtils::printk("Page fault.\n");
	while (1);
}

void exc_kernel_fpu(ProcessorRegisterSet* isr_registers)
{
	PrintUtils::printk("Kernel FPU error.\n");
	while (1);
}

void exc_align_check(ProcessorRegisterSet* isr_registers)
{
	PrintUtils::printk("Align check error.\n");
	while (1);
}

void exc_machine_check(ProcessorRegisterSet* isr_registers)
{
	PrintUtils::printk("Machine check exception.\n");
	while (1);
}

void exc_xm(ProcessorRegisterSet* isr_registers)
{
	PrintUtils::printk("SIMD FP.\n");
	while (1);
}

void exc_virtualization(ProcessorRegisterSet* isr_registers)
{
	PrintUtils::printk("Kernel virtualization exception.\n");
	while (1);
}

Span<IsrEntry_t> InterruptServiceRoutineEntries::get_interrupt_handlers_array()
{
	IsrEntry_t isr_entries_array[this->ISR_ENTRIES_SIZE];
	MemoryUtils::memset(isr_entries_array, NULL, this->_isr_entries.size());
	Span<IsrEntry_t> isr_entries = Span<IsrEntry_t>(isr_entries_array, this->ISR_ENTRIES_SIZE);

	IsrEntry_t interrupt_handlers_array[this->RAW_ISR_ENTRIES_SIZE] = {
		IsrEntry_t(InterruptCode::DIV_BY_ZERO, exc_divide_by_zero),
		IsrEntry_t(InterruptCode::DEBUG, exc_debug),
		IsrEntry_t(InterruptCode::NON_MASKABLE_INT, exc_non_maskable_int),
		IsrEntry_t(InterruptCode::BREAKPOINT, exc_breakpoint),
		IsrEntry_t(InterruptCode::OVERFLOW, exc_overflow),
		IsrEntry_t(InterruptCode::BOUND_RANGE, exc_bound_range),
		IsrEntry_t(InterruptCode::INV_OPCODE, exc_invopcode),
		IsrEntry_t(InterruptCode::DEVICE_UNAVAILABLE, exc_device_unavailable),
		IsrEntry_t(InterruptCode::DOUBLE_FAULT, exc_double_fault),
		IsrEntry_t(InterruptCode::INV_TSS, exc_invtss),
		IsrEntry_t(InterruptCode::NOT_PRESENT, exc_segment_not_present),
		IsrEntry_t(InterruptCode::STACK_SEGMANT_FAULT, exc_stack_segment_fault),
		IsrEntry_t(InterruptCode::GENRAL_PROTECTION_FAULT, exc_gpf),
		IsrEntry_t(InterruptCode::PAGE_FAULT, exc_pf),
		IsrEntry_t(InterruptCode::KERNEL_FPU, exc_kernel_fpu),
		IsrEntry_t(InterruptCode::ALIGN_CHECK, exc_align_check),
		IsrEntry_t(InterruptCode::MACHINE_CHECK, exc_machine_check),
		IsrEntry_t(InterruptCode::SIMF_FP, exc_xm),
		IsrEntry_t(InterruptCode::VIRTUALIZATION, exc_virtualization)
	};

	isr_entries.copy_from(Span<IsrEntry_t>(interrupt_handlers_array, this->RAW_ISR_ENTRIES_SIZE), this->RAW_ISR_ENTRIES_SIZE);

	return isr_entries;
}

InterruptServiceRoutineEntries::InterruptServiceRoutineEntries()
{
	this->_isr_entries = Span<IsrEntry_t>(this->get_interrupt_handlers_array());
}

Span<IsrEntry_t> InterruptServiceRoutineEntries::get_isr_entries()
{
	return this->_isr_entries;
}
