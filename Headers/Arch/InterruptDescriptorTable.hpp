#pragma once

#include <stdint.h>

#include "OsDefenitions/stddef.h"
#include "Utils/Span.hpp"
#include "Utils/Vector.hpp"
#include "InterruptServiceRoutine/InterruptServiceRoutineEntries.hpp"

extern "C" void load_idt(IdtDescriptor* idt_descriptor);

struct __attribute__((packed)) IdtEntry
{
	// TODO: can i use PointerValue instead of uint_<16|32>t(s) here
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
	size_t size;
	IdtEntry addr;
};

class InterruptDescriptorTable
{
public:
	InterruptDescriptorTable();

public:
	Span<IdtEntry> getEntries();
	IdtDescriptor* getIdtDescriptor();

private:
	void idt_set_entry(uint8_t entry_number, IsrFunction funcall);
	void set_all_idt_entries();

private:
	Span<IdtEntry> _entries;
	constexpr static uint16_t IDT_SIZE = 256;
	alignas(uint16_t) IdtDescriptor* _idt_descriptor;
};
