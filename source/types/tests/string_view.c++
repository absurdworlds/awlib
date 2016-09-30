#include <aw/types/string_view.h>
#include <aw/utility/test.h>

TestFile( "aw::sv_literals" );

namespace aw {
Test(string_view_1) {
	Checks {
		using namespace std::string_literals;
		using namespace aw::sv_literals;
		// TODO: actually fix?
		TestAssert(make_string_view({'t','e','s','t'}) == "test"s);
		TestAssert(" ooo\n"_s == " ooo\n");
	}
}
} // namespace aw
