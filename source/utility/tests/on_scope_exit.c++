#include <aw/utility/on_scope_exit.h>
#include <aw/utility/test.h>

TestFile( "on_scope_exit" );

namespace aw {
Test(scope_basic_test)
{
	int x = 100;
	auto on_exit1 = aw::call_on_exit([&] {x = 0;});
	{
		decltype(on_exit1) on_exit2(std::move(on_exit1));

		TestAssert(x == 100);
	}
	TestAssert(x == 0);
}
} // namespace aw

RunTests();
