#include "stdint.h"

#include "Vector.hpp"
#include "Macros.hpp"
#include "Utils/Functions/PrintUtils.hpp"
#include "Utils/Functions/MemoryUtils.hpp"
#include "Arch/InterruptServiceRoutine/InterruptServiceRoutineEntries.hpp"

void exc_divide_by_zero(IsrRegisters& isr_registers)
{
	PrintUtils::printk("Divide by zero at %x\n", isr_registers.rip);
	while(1);
}

void exc_debug(IsrRegisters& isr_registers)
{
	PrintUtils::printk("Debug!\n");
	while (1);
}

void exc_non_maskable_int(IsrRegisters& isr_registers)
{
	PrintUtils::printk("Non maskable interrupt!\n");
	while (1);
}

void exc_breakpoint(IsrRegisters& isr_registers)
{
	PrintUtils::printk("Breakpoint at %x\n", isr_registers.rip);
	// TODO: add input check for enter in order to continue.
}

void exc_overflow(IsrRegisters& isr_registers)
{
	PrintUtils::printk("Overflow!\n");
	while (1);
}

void exc_bound_range(IsrRegisters& isr_registers)
{
	PrintUtils::printk("Bound range exceeded.\n");
	while (1);
}

void exc_invopcode(IsrRegisters& isr_registers)
{
	PrintUtils::printk("Invalid opcode at %x\n", isr_registers.rip);
	while(1);
}

void exc_device_unavailable(IsrRegisters& isr_registers)
{
	PrintUtils::printk("Device not available.\n");
	while (1);
}

void exc_double_fault(IsrRegisters& isr_registers)
{
	PrintUtils::printk("Double fault, halting.\n");
	while(1);
}

void exc_invtss(IsrRegisters& isr_registers)
{
	PrintUtils::printk("TSS invalid.\n");
	while (1);
}

void exc_segment_not_present(IsrRegisters& isr_registers)
{
	PrintUtils::printk("Segment not present.\n");
	while (1);
}

void exc_stack_segment_fault(IsrRegisters& isr_registers)
{
	PrintUtils::printk("Stacksegment faulted.\n");
	while (1);
}

void exc_gpf(IsrRegisters& isr_registers)
{
	PrintUtils::printk("General protection fault at %x.\n", isr_registers.rip);
	while (1);
}

void exc_pf(IsrRegisters& isr_registers)
{
	PrintUtils::printk("Page fault.\n");
	while (1);
}

void exc_kernel_fpu(IsrRegisters& isr_registers)
{
	PrintUtils::printk("Kernel FPU error.\n");
	while (1);
}

void exc_align_check(IsrRegisters& isr_registers)
{
	PrintUtils::printk("Align check error.\n");
	while (1);
}

void exc_machine_check(IsrRegisters& isr_registers)
{
	PrintUtils::printk("Machine check exception.\n");
	while (1);
}

void exc_xm(IsrRegisters& isr_registers)
{
	PrintUtils::printk("SIMD FP.\n");
	while (1);
}

void exc_virtualization(IsrRegisters& isr_registers)
{
	PrintUtils::printk("Kernel virtualization exception.\n");
	while(1);
}

Span<const IsrEntry> InterruptServiceRoutineEntries::get_interrupt_handlers_array()
{
	// must be static otherwise we get "expression must have a constant value" on Span constructor 
	static constexpr IsrEntry raw_isr_entries[] =
	{
		IsrEntry(InterruptCode::DIV_BY_ZERO, exc_divide_by_zero),
		IsrEntry(InterruptCode::DEBUG, exc_debug),
		IsrEntry(InterruptCode::NON_MASKABLE_INT, exc_non_maskable_int),
		IsrEntry(InterruptCode::BREAKPOINT, exc_breakpoint),
		IsrEntry(InterruptCode::OVERFLOW, exc_overflow),
		IsrEntry(InterruptCode::BOUND_RANGE, exc_bound_range),
		IsrEntry(InterruptCode::INV_OPCODE, exc_invopcode),
		IsrEntry(InterruptCode::DEVICE_UNAVAILABLE, exc_device_unavailable),
		IsrEntry(InterruptCode::DOUBLE_FAULT, exc_double_fault),
		IsrEntry(InterruptCode::INV_TSS, exc_invtss),
		IsrEntry(InterruptCode::NOT_PRESENT, exc_segment_not_present),
		IsrEntry(InterruptCode::STACK_SEGMANT_FAULT, exc_stack_segment_fault),
		IsrEntry(InterruptCode::GENRAL_PROTECTION_FAULT, exc_gpf),
		IsrEntry(InterruptCode::PAGE_FAULT, exc_pf),
		IsrEntry(InterruptCode::KERNEL_FPU, exc_kernel_fpu),
		IsrEntry(InterruptCode::ALIGN_CHECK, exc_align_check),
		IsrEntry(InterruptCode::MACHINE_CHECK, exc_machine_check),
		IsrEntry(InterruptCode::SIMF_FP, exc_xm),
		IsrEntry(InterruptCode::VIRTUALIZATION, exc_virtualization)
	};

	constexpr Span<const IsrEntry> isr_entries (raw_isr_entries, SIZE_OF_ARRAY(raw_isr_entries));

	return isr_entries;
}

InterruptServiceRoutineEntries::InterruptServiceRoutineEntries()
{
	this->_isr_entries = Span<IsrEntry>(nullptr, this->ISR_ENTRIES_SIZE);
	MemoryUtils::memset(&this->_isr_entries, 0, this->_isr_entries.size());
	this->_isr_entries.copy_from(get_interrupt_handlers_array(), this->_isr_entries.size());
}

Span<IsrEntry> InterruptServiceRoutineEntries::get_isr_entries()
{
	return this->_isr_entries;
}

IsrRegisters* isr_function_handler(IsrRegisters& registers, InterruptServiceRoutineEntries& isr_entries)
{
	const IsrEntry isr_entry = isr_entries.get_isr_entries()[registers.interrupt_number];
	if (static_cast<int>(isr_entry.first()) == 0)
	{
		PrintUtils::printk("no iv for interrupt");
		while (1);
	}
	else
	{
		isr_entry.second()(registers);
	}

	return &registers;
}
