#pragma once

#include "Span.hpp"
#include "InterruptServiceRoutineDefenitions.hpp"

extern "C" IsrRegisters* isr_function_handler(IsrRegisters& registers);

class InterruptServiceRoutineEntries
{
    public:
        InterruptServiceRoutineEntries();

    public:
        Span<const IsrEntry> get_isr_entries();
        void set_isr_entries(Span<std::add_const_t<IsrEntry>>);

    private:
        Span<const IsrEntry> _isr_entries;
};