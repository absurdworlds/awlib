#include <aw/types/string_view.h>
#include <aw/test/test.h>

TestFile( "aw::sv_literals" );

namespace aw {
Test(string_view_1) {
	Checks {
		using namespace std::string_view_literals;
		// TODO: actually fix?
		TestAssert(make_string_view({'t','e','s','t'}) == "test"sv);
	}
}
} // namespace aw
