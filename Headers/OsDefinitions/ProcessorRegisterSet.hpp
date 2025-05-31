#pragma once

#include <stdint.h>

#include "OsDefenitions/stddef.h"

struct __attribute__((packed)) ProcessorRegisterSet
{
	uint16_t ds, es, fs, gs;
	uint64_t rax, rbx, rcx, rdx, rsi, rdi, rbp;
	uint64_t r8, r9, r10, r11, r12, r13, r14, r15;
	uint64_t interrupt_number, error_code;
	uint64_t rip;
	uint64_t cs;
	uint64_t rflags;
	uint64_t rsp;
	uint64_t ss;
};
