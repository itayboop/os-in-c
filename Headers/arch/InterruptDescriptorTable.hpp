#pragma once
#include <stdint.h>

#include "Utils/Span.hpp"
#include "Utils/Vector.hpp"
#include "InterruptServiceRoutineDefenitions.hpp"

struct __attribute__((packed)) IdtEntry
{
	// TODO: can we use PointerValue instead of uint_<16|32>t(s) here
	uint16_t offset_low;	       // offset bits 0..15
	uint16_t selector;	// a code segment selector in GDT
	uint8_t ist_index;
	uint8_t type_attributes;
	uint16_t offset_mid;	// offset bits 16..31
	uint32_t offset_high;	// offset bits 32..63
	uint8_t reserved;
};

struct __attribute__((packed)) IdtDescriptor
{
	uint16_t size;
	IdtEntry* addr;
};

extern "C" void load_idt(IdtDescriptor* idt_descriptor);

class InterruptDescriptorTable
{
	public:
		explicit InterruptDescriptorTable(const Span<IsrFunction>& functions);

	public:
		IdtEntry* getEntries();
		IdtDescriptor* getIdtDescriptor();

	private:
		void idt_set_entry(uint8_t entry_number, IsrFunction funcall);
		void register_interrupt_handler(InterruptCode interrupt_number, IsrHandlerFunction handler_func);

	private:
		static constexpr uint32_t INTERRUPT_DESCRIPTORS_COUNT = 256;

	private:
		Vector<IdtEntry, INTERRUPT_DESCRIPTORS_COUNT> _entries;
		alignas(uint16_t) IdtDescriptor* _idt_descriptor;
};
