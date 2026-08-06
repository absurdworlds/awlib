#include <aw/types/string_view.h>
#include <aw/test/test.h>

TestFile( "aw::sv_literals" );

namespace aw {
Test(string_view_1) {
	Checks {
		using namespace std::string_view_literals;
		TestAssert(make_string_view({'t','e','s','t'}) == "test"sv);
		TestAssert(make_string_view("test") == "test"sv);
		TestAssert(make_string_view("test").size() == 4);
	}
}

Test(string_view_embedded_nul) {
	Checks {
		using namespace std::string_view_literals;
		// only one null must be dropped
		TestAssert(make_string_view("\0\0\0").size() == 3);
		TestAssert(make_string_view("a\0b") == "a\0b"sv);
	}
}

Test(string_view_empty) {
	Checks {
		TestAssert(make_string_view("").size() == 0);
	}
}
} // namespace aw
