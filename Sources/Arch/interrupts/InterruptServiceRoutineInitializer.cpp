#include "Arch/InterruptServiceRoutine/InterruptServiceRoutineInitializer.hpp"

InterruptServiceRoutineEntries* g__interrupt_service_routine_entries;

InterruptServiceRoutineInitializer::InterruptServiceRoutineInitializer()
{
    // TODO: why did tubul tell me to initialize B before assignment if there is a default constructor? also why not instantiate it without a field?
    InterruptServiceRoutineEntries* g__interrupt_service_routine_entries = &this->interrupt_service_routine_entries;
}