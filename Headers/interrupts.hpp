#pragma once

#include "../Headers/idt.hpp"

#define EXC_DE  0
#define EXC_DB  1
#define EXC_NMI 2
#define EXC_BP  3
#define EXC_OF  4
#define EXC_BR  5
#define EXC_UD  6
#define EXC_NM  7
#define EXC_DF  8
#define EXC_TS  10
#define EXC_NP  11
#define EXC_SS  12
#define EXC_GP  13
#define EXC_PF  14
#define EXC_MF  16
#define EXC_AC  17
#define EXC_MC  18
#define EXC_XM  19
#define EXC_VE  20

void register_all_interrupt_handlers();
