#pragma once

#include <stddef.h>

extern "C"
{
void init_heap(void *base, size_t size);
void *malloc(size_t size);
void free(void *);
}

