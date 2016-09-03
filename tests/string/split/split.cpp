#include <stdio.h>
#include <utility>

#include <aw/utility/string/join.h>
#include <aw/utility/string/split.h>

int main(int c, char** a)
{
	using namespace aw::string;

	if (c < 3)
		return 1;

	std::string string = a[1];
	std::string delim = a[2];

	auto test = [&] (auto func) {
		auto bits = func(string, delim);

		for (auto bit : bits)
			puts(bit.c_str());
	};

	puts("split():");
	test(split);
	puts("explode():");
	test(explode);

	puts("join():");
	auto bits  = split(string, delim);
	auto joined = join(bits, delim);

	puts(joined.c_str());

	return 0;
}
