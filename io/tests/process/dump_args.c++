#include <fstream>

// simple test executable to test process api wrappers
int main(int, char** argv)
{
	// TODO: temp_file
	std::ofstream f("argv.txt");
	while (auto str = *argv++)
		f << str << std::endl;
}
