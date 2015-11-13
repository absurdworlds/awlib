#include <stdio.h>
#include <utility>

#include <awengine/string/utility.h>

int main (int c, char** a)
{
	using namespace awrts::string;

	if (c < 3) {
		return 1;
	}

	std::string string = a[1];
	std::string delim = a[2];

	auto test = [&] (auto func) {
				
		auto bits = func(string, delim);

		for (auto bit : bits) {
			printf("%s\n", bit.c_str());
		}
	};

	printf("split():\n");
	test(split);
	printf("explode():\n");
	test(explode);
	{
	}

	return 0;
}
