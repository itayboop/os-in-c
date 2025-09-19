#include "../../../Headers/arch/Interrupts/APIC.hpp"

#define APIC_READ(off) *((volatile uint32_t*)(m_base + off))
#define APIC_WRITE(off, val) (*((volatile uint32_t*)(m_base + off)) = val)

APIC::APIC()
{
    this->initialize();
}

uint64_t APIC::read_base()
{
    uint64_t low;
    uint64_t high;
    asm("rdmsr" : "=a"(low), "=d"(high) : "c"(0x1B));

    return (high << 32) | low;
}

void APIC::write_base(uint64_t base)
{
    uint64_t low = base & 0xFFFFFFFF;
    uint64_t high = base >> 32;
    asm("wrmsr" ::"a"(low), "d"(high), "c"(0x1B));
}

void APIC::enable()
{
    write_base(this->read_base() | (1UL << 11));

    APIC_WRITE(LOCAL_APIC_SIVR, APIC_READ(LOCAL_APIC_SIVR) | 0x1FF); // spurious interrupt vector
}

int APIC::initialize()
{
    m_base = this->read_base() & LOCAL_APIC_BASE;

    return 0;
}




