#include "Pointer.hpp"
#include "MemoryUtils.hpp"
#include "Arch/InterruptDescriptorTable.hpp"

void InterruptDescriptorTable::idt_set_entry(uint8_t entry_number, IsrFunction target_function)
{
	IdtEntry entry = this->_entries[entry_number];

	const Pointer* function_ptr = reinterpret_cast<const Pointer*>(target_function);
	entry.offset_high = function_ptr->high;
	entry.offset_mid = function_ptr->middle;
	entry.offset_low = function_ptr->low;

	entry.type_attributes = 0xEF;
	entry.ist_index = 0;
	entry.selector = 8; // CODE descriptor, see gdt64.code
}

void InterruptDescriptorTable::set_all_idt_entries()
{
	// GENERAL CPU INTERRUPTS
	idt_set_entry(0, isr0);
	idt_set_entry(1, isr1);
	idt_set_entry(2, isr2);
	idt_set_entry(3, isr3);
	idt_set_entry(4, isr4);
	idt_set_entry(5, isr5);
	idt_set_entry(6, isr6);
	idt_set_entry(7, isr7);
	idt_set_entry(8, isr8);
	idt_set_entry(9, isr9);
	idt_set_entry(10, isr10);
	idt_set_entry(11, isr11);
	idt_set_entry(12, isr12);
	idt_set_entry(13, isr13);
	idt_set_entry(14, isr14);
	idt_set_entry(15, isr15);
	idt_set_entry(16, isr16);
	idt_set_entry(17, isr17);
	idt_set_entry(18, isr18);
	idt_set_entry(19, isr19);
	idt_set_entry(20, isr20);
	idt_set_entry(21, isr21);
	idt_set_entry(22, isr22);
	idt_set_entry(23, isr23);
	idt_set_entry(24, isr24);
	idt_set_entry(25, isr25);
	idt_set_entry(26, isr26);
	idt_set_entry(27, isr27);
	idt_set_entry(28, isr28);
	idt_set_entry(29, isr29);
	idt_set_entry(30, isr30);
	idt_set_entry(31, isr31);
	idt_set_entry(32, isr32);
	idt_set_entry(33, isr33);
	idt_set_entry(34, isr34);
	idt_set_entry(35, isr35);
	idt_set_entry(36, isr36);
	idt_set_entry(37, isr37);
	idt_set_entry(38, isr38);
	idt_set_entry(39, isr39);
	idt_set_entry(40, isr40);
	idt_set_entry(41, isr41);
	idt_set_entry(42, isr42);
	idt_set_entry(43, isr43);
	idt_set_entry(44, isr44);
	idt_set_entry(45, isr45);
	idt_set_entry(46, isr46);
	idt_set_entry(47, isr47);
}

InterruptDescriptorTable::InterruptDescriptorTable()
{
	this->_entries = Span<IdtEntry>(nullptr, this->IDT_SIZE);
	MemoryUtils::memset(&this->_entries, 0, this->IDT_SIZE);

	this->_idt_descriptor->addr = this->_entries[0];
	this->_idt_descriptor->size = sizeof(this->_entries) - 1;

	this->set_all_idt_entries();

	load_idt(this->_idt_descriptor);
}

Span<IdtEntry> InterruptDescriptorTable::getEntries()
{
	return this->_entries;
};

IdtDescriptor* InterruptDescriptorTable::getIdtDescriptor()
{
	return this->_idt_descriptor;
};
