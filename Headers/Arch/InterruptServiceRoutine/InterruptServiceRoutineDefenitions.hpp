#pragma once
#include <cstdint>

#include "Utils/Pair.hpp"
#include "Arch/OsDefinitions.hpp"
#include "Arch/InterruptDescriptorTable.hpp"

enum class InterruptCode : uint8_t
{
	DIV_BY_ZERO = 0,
	DEBUG,
	NON_MASKABLE_INT,
	BREAKPOINT,
	OVERFLOW,
	BOUND_RANGE,
	INV_OPCODE,
	DEVICE_UNAVAILABLE,
	DOUBLE_FAULT,
	INV_TSS = 10,
	NOT_PRESENT,
	STACK_SEGMANT_FAULT,
	GENRAL_PROTECTION_FAULT,
	PAGE_FAULT,
	KERNEL_FPU = 16,
	ALIGN_CHECK,
	MACHINE_CHECK,
	SIMF_FP,
	VIRTUALIZATION,
};

struct __attribute__((packed)) IsrRegisters : public ProcessorRegisterSet
{
	uint64_t interrupt_number, error_code;
};

using IsrFunction = void(*)(void);
using IsrHandlerFunction = void(*)(IsrRegisters& registers);
using IsrEntry = Pair<InterruptCode, IsrHandlerFunction>;

extern "C" void isr0();
extern "C" void isr1();
extern "C" void isr2();
extern "C" void isr3();
extern "C" void isr4();
extern "C" void isr5();
extern "C" void isr6();
extern "C" void isr7();
extern "C" void isr8();
extern "C" void isr9();
extern "C" void isr10();
extern "C" void isr11();
extern "C" void isr12();
extern "C" void isr13();
extern "C" void isr14();
extern "C" void isr15();
extern "C" void isr16();
extern "C" void isr17();
extern "C" void isr18();
extern "C" void isr19();
extern "C" void isr20();
extern "C" void isr21();
extern "C" void isr22();
extern "C" void isr23();
extern "C" void isr24();
extern "C" void isr25();
extern "C" void isr26();
extern "C" void isr27();
extern "C" void isr28();
extern "C" void isr29();
extern "C" void isr30();
extern "C" void isr31();
extern "C" void isr32();
extern "C" void isr33();
extern "C" void isr34();
extern "C" void isr35();
extern "C" void isr36();
extern "C" void isr37();
extern "C" void isr38();
extern "C" void isr39();
extern "C" void isr40();
extern "C" void isr41();
extern "C" void isr42();
extern "C" void isr43();
extern "C" void isr44();
extern "C" void isr45();
extern "C" void isr46();
extern "C" void isr47();
