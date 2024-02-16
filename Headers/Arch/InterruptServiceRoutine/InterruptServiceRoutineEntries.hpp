#pragma once

#include "Utils/Span.hpp"
#include "InterruptServiceRoutineDefenitions.hpp"

extern "C" IsrRegisters* isr_function_handler(IsrRegisters& registers);

class InterruptServiceRoutineEntries
{
public:
    InterruptServiceRoutineEntries();

public:
    Span<IsrEntry_t> get_isr_entries();

private:
    Span<const IsrEntry_t> get_interrupt_handlers_array();

private:
    Span<IsrEntry_t> _isr_entries;
	constexpr static uint16_t ISR_ENTRIES_SIZE = 256;
};
