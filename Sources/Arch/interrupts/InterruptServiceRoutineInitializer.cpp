#include "Arch/InterruptServiceRoutine/InterruptServiceRoutineInitializer.hpp"

InterruptServiceRoutineEntries* g__interrupt_service_routine_entries;

InterruptServiceRoutineInitializer::InterruptServiceRoutineInitializer()
{
    this->interrupt_service_routine_entries = InterruptServiceRoutineEntries();
    g__interrupt_service_routine_entries = &this->interrupt_service_routine_entries;
    PrintUtils::printk("%x\n", g__interrupt_service_routine_entries);
}