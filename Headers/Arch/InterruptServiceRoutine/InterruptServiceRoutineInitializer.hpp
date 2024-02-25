#pragma once
#include "InterruptServiceRoutineEntries.hpp"

extern "C" InterruptServiceRoutineEntries* g__interrupt_service_routine_entries;

class InterruptServiceRoutineInitializer
{
public:
    InterruptServiceRoutineInitializer();

private:
    InterruptServiceRoutineEntries interrupt_service_routine_entries;
};
