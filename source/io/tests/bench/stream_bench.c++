#include <aw/io/input_file_stream.h>
#include <aw/io/input_stream_utils.h>
#include <fstream>
#include <iostream>
namespace aw {

[[using gnu: used, noinline]] void use(std::string& s) { }

fs::path f{ "file.txt" };
void mystream()
{
	std::string line;
	io::input_file_stream ifs{ f };
	for (int i = 0; i < 1000; ++i) {
		while(ifs.read_until( line,'\n')) use(line);
	}
}

void notmysteream()
{
	std::string line;
	std::ifstream ifs{ f };
	for (int i = 0; i < 1000; ++i) {
		while(getline( ifs, line)) use(line);
	}
}


} // namespace aw

#include <chrono>
int main()
{
	{
	auto t0 = std::chrono::steady_clock::now();
	aw::mystream();
	auto t1 = std::chrono::steady_clock::now();
	std::cerr << std::chrono::duration<double>( t1 - t0 ).count() << "s\n";
	}

	{
	auto t0 = std::chrono::steady_clock::now();
	aw::notmysteream();
	auto t1 = std::chrono::steady_clock::now();
	std::cerr << std::chrono::duration<double>( t1 - t0 ).count() << "s\n";
	}
}
