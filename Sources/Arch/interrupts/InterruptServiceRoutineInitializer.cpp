#include "Arch/InterruptServiceRoutine/InterruptServiceRoutineInitializer.hpp"

InterruptServiceRoutineEntries *g__interrupt_service_routine_entries;

InterruptServiceRoutineInitializer::InterruptServiceRoutineInitializer() : interrupt_service_routine_entries()
{
	g__interrupt_service_routine_entries = &this->interrupt_service_routine_entries;
}
