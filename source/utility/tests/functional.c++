#include <aw/utility/functional/overload.h>
#include <aw/utility/test.h>

TestFile( "on_scope_exit" );

namespace aw {
Test(overload_compile_test)
{
	auto func = overload(
	[] (string_view s) { return std::string(s) + "sv"; },
	[] (std::string s) { return s + "s"; }
	);

	using namespace std::string_literals;
	using namespace std::string_view_literals;
	TestEqual(func("A"sv), "Asv");
	TestEqual(func("B"s),  "Bs");
}
} // namespace aw
