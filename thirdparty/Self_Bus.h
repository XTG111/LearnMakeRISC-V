#pragma once
#ifndef _SELF_BUS_H_
#define _SELF_BUS_H_

#include "Self_DRAM.h"
class BUS
{
private:
	//内存
	DRAM dram;
public:
	BUS(const std::vector<uint8_t>& code);

	uint64_t load(uint64_t addr, uint64_t size);
	void store(uint64_t addr, uint64_t size, uint64_t value);
	inline std::vector<uint8_t> GetDRAM() { return dram.GetDRAM(); }
};
#endif // !_BUS_H_

