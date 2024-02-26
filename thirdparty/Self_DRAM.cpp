#include "Self_DRAM.h"
#include "DramType.h"
#include <stdexcept>

DRAM::DRAM(const std::vector<uint8_t>& code)
{
	//初始化dram DRAM_SIZE为自定义的内存总容量
	dram.resize(DRAM_SIZE, 0);
	//利用copy将code中的数据复制给dram
	std::copy(code.begin(), code.end(), dram.begin());
}

uint64_t DRAM::load(uint64_t addr, uint64_t size)
{
	//只能读取长度为8，16，32，64
	if (size != 8 && size != 16 && size != 32 && size != 64)
	{
		throw std::runtime_error("LoadAccessFault");
	}

	//计算读取长度对应vector的元素个数
	uint64_t nbytes = size / 8;
	//计算对应的起始位置
	std::size_t index = addr - DRAM_BASE;
	//如果读取超过了内存大小
	if (index + nbytes > dram.size())
	{
		throw std::out_of_range("Address out of range");
	}

	//返回结果
	uint64_t value = 0;
	for (uint64_t i = 0; i < nbytes; i++)
	{
		value |= static_cast<uint64_t>(dram[index + i]) << (i * 8);
	}

	return value;
}

void DRAM::store(uint64_t addr, uint64_t size, uint64_t value)
{
	if (size != 8 && size != 16 && size != 32 && size != 64) {
		throw std::runtime_error("StoreAMOAccessFault");
	}
	uint64_t nbytes = size / 8;
	std::size_t index = addr - DRAM_BASE;
	if (index + nbytes > dram.size()) {
		throw std::out_of_range("Address out of range");
	}
	//写入
	for (uint64_t i = 0; i < nbytes; ++i) {
		dram[index + i] = (value >> (i * 8)) & 0xFF;
	}
}

