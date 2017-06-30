#include <aw/utility/functional/overload.h>
#include <aw/utility/functional/trivial.h>
#include <aw/utility/functional/wrapper.h>
#include <aw/utility/test.h>
#include <vector>
#include <memory>
#include <algorithm>

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

Test(trivial_compile_test)
{
	std::vector vec{1, 2, 3, 4, 5};

	auto it1 = std::find_if(begin(vec), end(vec), false_func{});
	auto it2 = std::find_if(begin(vec), end(vec), true_func{});
	TestAssert(it1 == end(vec));
}

void do_nothing(void*) {};

Test(wrapper_compile_test)
{
	std::unique_ptr<void, function_wrapper<do_nothing>> ptr;
}
} // namespace aw
