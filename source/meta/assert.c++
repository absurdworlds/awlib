#include <aw/utility/assert.h>

#include <iostream>

namespace aw {

void assert_fail(const char* assertion, std::source_location location)
{
	std::cerr << "ASSERTION FAILED:" << assertion << ' ' << location.file_name() << '\n';
}

}

bool test()

{
	std::cerr << false;
	return false;
}


int main()
{
	aw_assert(test());
	aw_assert(test(), develop, "mymesg");
	aw_assert(test(), normal);
	aw_assert(test(), audit);
}
