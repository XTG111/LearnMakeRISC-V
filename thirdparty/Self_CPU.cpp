#include "Self_CPU.h"

uint32_t CPU::fetch()
{
    size_t index = static_cast<size_t>(pc);
    
    //小端实现 如果高位数据比如01020304排列将是大端实现
    //利用位或符号实现组合
    uint32_t inst = static_cast<uint32_t>(DRAM[index]) |
        static_cast<uint32_t>(DRAM[index + 1] << 8) |
        static_cast<uint32_t>(DRAM[index + 2] << 16) |
        static_cast<uint32_t>(DRAM[index + 3] << 24);

    return inst;
}

void CPU::execute(uint32_t inst)
{
    //获取操作码 opcode inst中0-6位
    uint32_t opcode = inst & 0x7f;
    //获取目标寄存器 rd inst中7-11位
    uint32_t rd = (inst >> 7) & 0x1f;
    //获取源寄存器1 rs1 inst中15-19位
    uint32_t rs1 = (inst >> 15) & 0x1f;
    //获取源寄存器2 rs2 inst中20-24位
    uint32_t rs2 = (inst >> 20) & 0x1f;
    //获取功能码1 funct3 inst中12-14位
    uint32_t funct3 = (inst >> 12) & 0x7;
    //获取功能码2 funct7 inst中25-31位
    uint32_t funct7 = (inst >> 25) & 0x7f;


    //寄存器0
    REGs[0] = 0;

    //执行读取到的指令 add addi
    switch (opcode)
    {
    case 0x13:{
        //addi
        //获取立即数 imm inst中的最高20位是为带符号扩展的立即数
        int64_t imm = static_cast<uint32_t>(inst & 0xfff00000) >> 20;
        //加法操作
        REGs[rd] = REGs[rs1] + imm;
        break;
	}
    case 0x33:{
        //add
        REGs[rd] = REGs[rs1] + REGs[rs2];
        break;
	}
    default:
        std::cerr << "Invaild Opcode: " << std::hex << opcode << std::endl;
        break;
    }
}

void CPU::dump_registers()
{
    //分隔线
    std::cout << std::setw(80) << std::setfill('-') << "" << std::endl;
    //重置填充
    std::cout << std::setfill(' ');
    //打印
    for (size_t i = 0; i < 32; i += 4)
    {
        std::cout << std::setw(4) << "x" << i << "(" << RVABI[i] << ") = " << std::hex << std::setw(16) << std::setfill('0') << REGs[i] << " "
            << std::setw(4) << "x" << i + 1 << "(" << RVABI[i + 1] << ") = " << std::setw(16) << REGs[i + 1] << " "
            << std::setw(4) << "x" << i + 2 << "(" << RVABI[i + 2] << ") = " << std::setw(16) << REGs[i + 2] << " "
            << std::setw(4) << "x" << i + 3 << "(" << RVABI[i + 3] << ") = " << std::setw(16) << REGs[i + 3] << std::endl;
    }
}

