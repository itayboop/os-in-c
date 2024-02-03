#pragma once
#include "InterruptServiceRoutineEntries.hpp"

extern InterruptServiceRoutineEntries* g__interrupt_service_routine_entries;

class InterruptServiceRoutineInitializer
{
public:
    InterruptServiceRoutineInitializer();

private:
    static InterruptServiceRoutineEntries interrupt_service_routine_entries;
};
