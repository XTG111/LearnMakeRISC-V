#pragma once
#ifndef _SELF_CPU_H_
#define _SELF_CPU_H_

#include <vector>
#include <array>
#include <cstdint>
#include <iostream>
#include <string>
#include <iomanip>
#include <optional>
#include "DramType.h"
#include "Self_Bus.h"
#include "Self_DRAM.h"

//CPU类
class CPU
{
private:
	//RISC-V的32个寄存器
	std::array<uint64_t, 32> REGs;
	//pc指针
	uint64_t pc;
	//bus总线
	BUS bus;
	//RISC-V寄存器名称
	const std::array<std::string, 32> RVABI = {
		"zero", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
		"s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
		"a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
		"s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6",
	};
public:
	//构造函数
	CPU(const std::vector<uint8_t>& code) :pc(DRAM_BASE),bus(code)
	{
		//初始化寄存器
		REGs.fill(0);
		//设置堆栈指针寄存器的初始值
		REGs[2] = DRAM_END;
	}

	//取指令操作 fetch 在dram中 从pc位置开始取长度为32的指令
	uint32_t fetch();

	//读取操作
	uint64_t load(uint64_t addr, uint64_t size);
	//写入操作
	void store(uint64_t addr, uint64_t size, uint64_t value);

	//执行指令的函数 execute 
	std::optional<uint64_t> execute(uint32_t inst);

	//输出打印每个寄存器的值
	void dump_registers();
	//输出打印pc指针
	void dump_pc() const;

public:
	inline void ChangePC(uint64_t new_pc) { pc = new_pc; }
	inline uint64_t GetPC() { return pc; }
	inline uint64_t update_pc() const {	return pc + 4; }
	inline std::vector<uint8_t> GetDRAM() { return bus.GetDRAM(); }
};
#endif // !_SELF_CPU_H_


