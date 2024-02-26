#include "Self_Bus.h"
#include "DramType.h"
#include <stdexcept>
#include <string>

BUS::BUS(const std::vector<uint8_t>& code):dram(code)
{
}

uint64_t BUS::load(uint64_t addr, uint64_t size)
{
    if (addr >= DRAM_BASE && addr <= DRAM_END)
    {
        return dram.load(addr, size);
    }
    else 
    {
        throw std::runtime_error("LoadAccessFault at address " + std::to_string(addr));
    }
}

void BUS::store(uint64_t addr, uint64_t size, uint64_t value)
{
    if (addr >= DRAM_BASE && addr <= DRAM_END) 
    {
        dram.store(addr, size, value);
    }
    else 
    {
        throw std::runtime_error("StoreAMOAccessFault at address " + std::to_string(addr));
    }
}

