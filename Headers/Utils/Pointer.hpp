#pragma once
#include <cstdint>

struct __attribute__((packed)) Pointer
{
	uint16_t low;
	uint16_t middle;
	uint32_t high;
};
