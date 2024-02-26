#include "thirdparty/Self_CPU.h"
#include "thirdparty/Exception.h"
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
	try {
		while (true) {
			uint32_t inst = cpu.fetch();
			auto new_pc = cpu.execute(inst);
			if (new_pc.has_value()) {
				cpu.ChangePC(new_pc.value());
			}
			else {
				break;
			}
		}
	}
	catch (const Exception& e) {
		std::cerr << "Exception main: " << e << std::endl;
	}

	//打印当前cpu状态
	cpu.dump_registers();
	return 0;
}
