#include <aw/types/support/enum.h>
#include <aw/test/test.h>

TestFile("enum bit operators");

namespace aw {
namespace {
enum class flags {
	none  = 0,
	read  = 1,
	write = 2,
	exec  = 4,
	all   = 7,
};
} // namespace

using namespace enum_bit_operators;

Test(enum_or) {
	Checks {
		TestEqual(underlying(flags::read | flags::write), 3);
		TestEqual(underlying(flags::read | flags::read), 1);
		TestEqual(underlying(flags::none | flags::exec), 4);
		TestEqual(underlying(flags::read | flags::write | flags::exec), 7);
	}
}

Test(enum_and) {
	Checks {
		TestEqual(underlying(flags::all & flags::write), 2);
		TestEqual(underlying(flags::read & flags::write), 0);
	}
}

Test(enum_xor) {
	Checks {
		TestEqual(underlying(flags::read ^ flags::write), 3);
		TestEqual(underlying(flags::read ^ flags::read), 0);
		TestEqual(underlying(flags::all ^ flags::write), 5);
	}
}

Test(enum_compound_assignment) {
	auto a = flags::read;
	a |= flags::write;

	auto b = flags::all;
	b &= flags::exec;

	auto c = flags::all;
	c ^= flags::read;

	Checks {
		TestEqual(underlying(a), 3);
		TestEqual(underlying(b), 4);
		TestEqual(underlying(c), 6);
	}
}
} // namespace aw
