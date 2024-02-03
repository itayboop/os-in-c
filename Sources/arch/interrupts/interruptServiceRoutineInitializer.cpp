#include "Headers/arch/InterruptServiceRoutine/InterruptServiceRoutineInitializer.hpp"

InterruptServiceRoutineInitializer::InterruptServiceRoutineInitializer()
{
    // TODO: why did tubul tell me to initialize B before assignment if there is a default constructor?
    g__interrupt_service_routine_entries = &this->interrupt_service_routine_entries;
}