#include "Self_CPU.h"
#include "Exception.h"

uint32_t CPU::fetch()
{
    if (pc >= DRAM_BASE && pc <= DRAM_END)
    {
        return bus.load(pc, 32);
    }
    else
    {
        throw std::runtime_error("FetchFault at address " + std::to_string(pc));
    }
}

uint64_t CPU::load(uint64_t addr, uint64_t size)
{
    if (addr >= DRAM_BASE && addr <= DRAM_END)
    {
        return bus.load(addr, size);
    }
    else
    {
        throw std::runtime_error("LoadAccessFault at address " + std::to_string(addr));
    }
}

void CPU::store(uint64_t addr, uint64_t size, uint64_t value)
{
    if (addr >= DRAM_BASE && addr <= DRAM_END)
    {
        bus.store(addr, size, value);
    }
    else
    {
        throw std::runtime_error("StoreAMOAccessFault at address " + std::to_string(addr));
    }
}

std::optional<uint64_t> CPU::execute(uint32_t inst)
{
    try {
        uint32_t opcode = inst & 0x7f;
        uint32_t rd = (inst >> 7) & 0x1f;
        uint32_t rs1 = (inst >> 15) & 0x1f;
        uint32_t rs2 = (inst >> 20) & 0x1f;
        uint32_t funct3 = (inst >> 12) & 0x7;
        uint32_t funct7 = (inst >> 25) & 0x7f;

        // x0 is hardwired zero
        REGs[0] = 0;

        std::cout << "Executing instruction: 0x" << std::hex << inst << std::dec << std::endl;

        // execute stage
        switch (opcode) {
        case 0x13: { // addi
            int64_t imm = static_cast<int32_t>(inst & 0xfff00000) >> 20;
            std::cout << "ADDI: x" << rd << " = x" << rs1 << " + " << imm << std::endl;
            REGs[rd] = REGs[rs1] + imm;
            return update_pc();
        }
        case 0x33: { // add
            std::cout << "ADD: x" << rd << " = x" << rs1 << " + x" << rs2 << std::endl;
            REGs[rd] = REGs[rs1] + REGs[rs2];
            return update_pc();
        }
        default: {
            throw Exception(Exception::Type::IllegalInstruction, opcode);
        }
        }
    }
    catch (const Exception& e) {
        std::cerr << "Exception execute : " << e << std::endl;
        return std::nullopt;  // 使用 std::optional 表示异常
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

void CPU::dump_pc() const
{
}


