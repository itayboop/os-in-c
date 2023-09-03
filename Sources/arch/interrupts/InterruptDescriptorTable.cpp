#include "InterruptDescriptorTable.hpp"
#include "Utils/Pointer.hpp"

InterruptDescriptorTable::InterruptDescriptorTable()
{
	// TODO: not to be such a noob
}

IdtEntry* InterruptDescriptorTable::getEntries()
{
	return this->_entries;
};

IdtDescriptor* InterruptDescriptorTable::getIdtDescriptor()
{
	return this->_idt_descriptor;
};

void InterruptDescriptorTable::idt_set_entry(uint8_t entry_number, IsrFunction target_function)
{
	IdtEntry* entry = &this->_entries[entry_number];

	const Pointer* function_ptr = reinterpret_cast<const Pointer*>(target_function);
	entry->offset_high = function_ptr->high;
	entry->offset_mid = function_ptr->middle;
	entry->offset_low = function_ptr->low;

	entry->type_attributes = 0xEF;
	entry->ist_index = 0;
	entry->selector = 8; // CODE descriptor, see gdt64.code
}
