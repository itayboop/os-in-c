#pragma once

#include <stdint.h>
#include "multiboot_types.h"

class Multiboot final
{
public:
    Multiboot(uint32_t magic, uintptr_t addr);

public:
    void parse_mb_info() const;
    void validate_multiboot_magic() const;

private:
    uint32_t _magic;
    uintptr_t _addr;

};