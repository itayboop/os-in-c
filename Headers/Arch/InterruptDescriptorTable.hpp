#pragma once

#include <stdint.h>
#include "OsDefenitions/stddef.h"

#include "Utils/Span.hpp"
#include "Utils/Vector.hpp"

#include "InterruptServiceRoutine/InterruptServiceRoutineEntries.hpp"
#include "InterruptServiceRoutine/InterruptServiceRoutineDefenitions.hpp"

extern "C" ProcessorRegisterSet * isr_function_handler(ProcessorRegisterSet * registers, InterruptServiceRoutineEntries * isr_entries);

struct __attribute__((packed)) IdtEntry
{
	// TODO: can i use PointerValue instead of uint_<16|32>t(s) here
	uint16_t isr_low;	       // offset bits 0..15
	uint16_t selector;	// a code segment selector in GDT
	uint8_t ist_index;
	uint8_t type_attributes;
	uint16_t isr_mid;	// offset bits 16..31
	uint32_t isr_high;	// offset bits 32..63
	uint8_t reserved;
};

struct __attribute__((packed)) IdtDescriptor
{
	uint16_t size;
	IdtEntry addr;
};

extern "C" void load_idt(IdtDescriptor * idt_descriptor);

class InterruptDescriptorTable
{
public:
	InterruptDescriptorTable();

public:
	Span<IdtEntry> getEntries();
	IdtDescriptor* getIdtDescriptor();

private:
	void idt_set_entry(uint8_t entry_number, IsrFunction_t* funcall);
	void set_all_idt_entries();

private:
	Span<IdtEntry> _entries;
	constexpr static uint16_t IDT_SIZE = 256;
	constexpr static uint16_t NO_INTERRUPT_HANDLER = 0;
	alignas(uint16_t) IdtDescriptor* _idt_descriptor;
};
