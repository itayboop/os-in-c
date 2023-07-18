#include <stdint.h>

#include "idt.hpp"
#include "utils.hpp"

IsrHandlerFunction interrupt_handlers[256] __attribute__((aligned(16)));
IdtDescriptor idt_ptr __attribute__((aligned(16)));
IdtEntry idt[256] __attribute__((aligned(16)));

void register_interrupt_handler(InterruptCode interrupt_number, IsrHandlerFunction handler_func)
{
	interrupt_handlers[static_cast<uint8_t>(interrupt_number)] = handler_func;
}

extern "C" {
	Registers* isr_function_handler(Registers& registers)
	{
		if (interrupt_handlers[registers.interrupt_number] == 0)
		{
			printf("no iv for interrupt");
			while (1);
		}
		else
		{
			interrupt_handlers[registers.interrupt_number](registers);
		}

	return &registers;
	}
}

void idt_set_entry(uint8_t entry_number, IsrFunction* funcall)
{
	IdtEntry* entry = &idt[entry_number];
	uintptr_t funcall_ptr = reinterpret_cast<uintptr_t>(funcall);

	entry->offset_high = (funcall_ptr >> 32) & 0xFFFFFFFF;
	entry->offset_mid = (funcall_ptr >> 16) & 0xFFFF;
	entry->offset_low = funcall_ptr & 0xFFFF;
	entry->type_attributes = 0xEF;
	entry->ist_index = 0;
	entry->selector = 8; // CODE descriptor, see gdt64.code
}

void initialize_idt()
{
	memset(idt, 0, sizeof(idt));
	memset(interrupt_handlers, 0, sizeof(interrupt_handlers));

	idt_ptr.size = (sizeof(idt)) - 1;
	idt_ptr.base = idt;

	// GENERAL CPU INTERRUPTS
	idt_set_entry(0, (IsrFunction*)isr0);
	idt_set_entry(1, (IsrFunction*)isr1);
	idt_set_entry(2, (IsrFunction*)isr2);
	idt_set_entry(3, (IsrFunction*)isr3);
	idt_set_entry(4, (IsrFunction*)isr4);
	idt_set_entry(5, (IsrFunction*)isr5);
	idt_set_entry(6, (IsrFunction*)isr6);
	idt_set_entry(7, (IsrFunction*)isr7);
	idt_set_entry(8, (IsrFunction*)isr8);
	idt_set_entry(9, (IsrFunction*)isr9);
	idt_set_entry(10, (IsrFunction*)isr10);
	idt_set_entry(11, (IsrFunction*)isr11);
	idt_set_entry(12, (IsrFunction*)isr12);
	idt_set_entry(13, (IsrFunction*)isr13);
	idt_set_entry(14, (IsrFunction*)isr14);
	idt_set_entry(15, (IsrFunction*)isr15);
	idt_set_entry(16, (IsrFunction*)isr16);
	idt_set_entry(17, (IsrFunction*)isr17);
	idt_set_entry(18, (IsrFunction*)isr18);
	idt_set_entry(19, (IsrFunction*)isr19);
	idt_set_entry(20, (IsrFunction*)isr20);
	idt_set_entry(21, (IsrFunction*)isr21);
	idt_set_entry(22, (IsrFunction*)isr22);
	idt_set_entry(23, (IsrFunction*)isr23);
	idt_set_entry(24, (IsrFunction*)isr24);
	idt_set_entry(25, (IsrFunction*)isr25);
	idt_set_entry(26, (IsrFunction*)isr26);
	idt_set_entry(27, (IsrFunction*)isr27);
	idt_set_entry(28, (IsrFunction*)isr28);
	idt_set_entry(29, (IsrFunction*)isr29);
	idt_set_entry(30, (IsrFunction*)isr30);
	idt_set_entry(31, (IsrFunction*)isr31);
	idt_set_entry(32, (IsrFunction*)isr32);
	idt_set_entry(33, (IsrFunction*)isr33);
	idt_set_entry(34, (IsrFunction*)isr34);
	idt_set_entry(35, (IsrFunction*)isr35);
	idt_set_entry(36, (IsrFunction*)isr36);
	idt_set_entry(37, (IsrFunction*)isr37);
	idt_set_entry(38, (IsrFunction*)isr38);
	idt_set_entry(39, (IsrFunction*)isr39);
	idt_set_entry(40, (IsrFunction*)isr40);
	idt_set_entry(41, (IsrFunction*)isr41);
	idt_set_entry(42, (IsrFunction*)isr42);
	idt_set_entry(43, (IsrFunction*)isr43);
	idt_set_entry(44, (IsrFunction*)isr44);
	idt_set_entry(45, (IsrFunction*)isr45);
	idt_set_entry(46, (IsrFunction*)isr46);
	idt_set_entry(47, (IsrFunction*)isr47);

	load_idt(&idt_ptr);
}
