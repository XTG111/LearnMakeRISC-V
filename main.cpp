#include "thirdparty/Self_CPU.h"
#include <fstream>
#include <streambuf>

int main(int argc,char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Usage:\n"
			<< "- ./program_name <filename>\n";
		return 0;
	}

	//读入文件
	std::ifstream file(argv[1], std::ios::binary);
	if (!file)
	{
		std::cerr << "Cannot open file: " << argv[1] << std::endl;
		return 1;
	}

	//利用istreambuf_iterator将file文件字符读入到code容器中，用于构造cpu的dram
	std::vector<uint8_t> code(std::istreambuf_iterator<char>(file), {});
	CPU cpu(code);

	//根据指令执行操作
	while (cpu.GetPC() << cpu.GetDRAM().size() * sizeof(cpu.GetDRAM()[0]))
	{
		uint32_t inst = cpu.fetch();
		cpu.execute(inst);
		cpu.PCAdd(4);
	}

	//打印当前cpu状态
	cpu.dump_registers();
	return 0;
}
