#pragma once
#ifndef _DRAMTYPE_H_
#define _DRAMTYPE_H_
#include <cstddef>

//使用 std::size_t 替代 uint64_t 来表示内存大小，更好地表达意图和增加可移植性

//DRAM_SIZE 128MB
constexpr std::size_t DRAM_SIZE = 1024 * 1024 * 128;
//DRAM 的基地址
constexpr std::size_t DRAM_BASE = 0x80000000;
//DRAM 的结束地址
constexpr std::size_t DRAM_END = DRAM_BASE + DRAM_SIZE - 1;

#endif // !_DRAMTYPE_H_

