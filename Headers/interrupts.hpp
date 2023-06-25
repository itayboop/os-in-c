#pragma once

#include "../Headers/idt.hpp"

#define EXC_DIV_BY_ZERO 0
#define EXC_DEBUG       1
#define EXC_NMI         2
#define EXC_BP          3
#define EXC_OVERFLOW    4
#define EXC_BR          5
#define EXC_INV_OPCODE  6
#define EXC_DU          7
#define EXC_DB_FAULT    8
#define EXC_INV_TSS     9
#define EXC_NOT_PRESENT 11
#define EXC_SSF         12
#define EXC_GP          13
#define EXC_PF          14
#define EXC_PRESERVED   15

void register_all_interrupt_handlers();
