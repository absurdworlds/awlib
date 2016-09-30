#include <aw/utility/string_view.h>
#include <aw/utility/test.h>

TestFile( "aw::sv_literals" );

namespace aw {
Test(string_view_1) {
	Checks {
		using namespace aw::sv_literals;
		TestAssert(make_string_view("test") == "test");
		TestAssert(" ooo\n"_s == " ooo\n");
	}
}
} // namespace aw
