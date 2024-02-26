#pragma once
#ifndef _SELF_CPU_H_
#define _SELF_CPU_H_

#include <vector>
#include <array>
#include <cstdint>
#include <iostream>
#include <string>
#include <iomanip>

//DRAM_SIZE 128MB
const uint64_t DRAM_SIZE = 1024 * 1024 * 128;

//CPU类
class CPU
{
private:
	//RISC-V的32个寄存器
	std::array<uint64_t, 32> REGs;
	//pc指针
	uint64_t pc;
	//内存 利用数组模拟
	std::vector<uint8_t> DRAM;
	//RISC-V寄存器名称
	const std::array<std::string, 32> RVABI = {
		"zero", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
		"s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
		"a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
		"s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6",
	};
public:
	//构造函数
	CPU(const std::vector<uint8_t>& dram) :pc(0), DRAM(dram)
	{
		//初始化寄存器
		REGs.fill(0);
		//设置堆栈指针寄存器的初始值
		REGs[2] = DRAM_SIZE - 1;
	}

	//取指令操作 fetch
	uint32_t fetch();

	//执行指令的函数 execute 
	void execute(uint32_t inst);

	//输出打印每个寄存器的值
	void dump_registers();

public:
	inline uint64_t GetPC() { return pc; }
	inline void PCAdd(int num) { pc += static_cast<uint64_t>(num); }
	inline std::vector<uint8_t> GetDRAM() { return DRAM; }
};
#endif // !_SELF_CPU_H_


