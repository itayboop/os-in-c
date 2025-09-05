#pragma once
#include "InterruptsDescriptorTable.hpp"

class InterruptSource {
public:
    virtual void register_handlers(InterruptDescriptorTable &idt) = 0;
    // TODO: add virtual destructor when memory management is implemented
};