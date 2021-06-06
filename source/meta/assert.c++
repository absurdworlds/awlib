#include <aw/utility/assert.h>

#include <iostream>

namespace aw {

void assert_fail(string_view assertion, std::source_location location)
{
	std::cerr << "ASSERTION FAILED:" << assertion << " in file " << location.file_name() << " on line " << location.line() << '\n';
}

}

bool test()
{
	std::cerr << "FAIL!\n";
	return false;
}


int main()
{
	aw_assert(test());
	aw_assert(test(), develop, "mymesg");
	aw_assert(test(), normal);
	aw_assert_x(test(), audit, "bad fault: %0", 1);
}
