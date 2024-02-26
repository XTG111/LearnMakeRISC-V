#pragma once
#ifndef _SELF_DRAM_H_
#define _SELF_DRAM_H_

#include <vector>
#include <cstdint>

class DRAM
{
private:
	//内存的实例表示DRAM中存入的数据
	std::vector<uint8_t> dram;

public:
	//构造函数，用于接受指令存入到数组中
	DRAM(const std::vector<uint8_t>& code);
	//从DRAM中读数据
	uint64_t load(uint64_t addr, uint64_t size);
	//向DRAM中写入数据
	void store(uint64_t addr, uint64_t size, uint64_t value);
	inline std::vector<uint8_t> GetDRAM() { return dram; }
};
#endif // !_SELF_DRAM_H_


