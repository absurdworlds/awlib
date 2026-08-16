#include <aw/utility/result.h>
#include <aw/test/test.h>
#include <aw/test/helpers/counted.h>

TestFile( "result" );

namespace aw {
using test::counted;

Test(result_basic_test)
{
	result<counted, int> val{ counted{counted::payload('a')} };
	result<counted, int> err{ 42, error_tag{} };

	TestAssert(bool(val));
	TestAssert(!err);
	TestEqual(val.value().value, counted::payload('a'));
	TestEqual(err.error(), 42);
}

Test(result_copy_owns_an_independent_value)
{
	counted::live = 0;
	{
		result<counted, int> original{ counted{counted::payload('v')} };
		TestEqual(counted::live, 1);
		{
			result<counted, int> copy{ original };
			// Both results now hold a live value of their own.
			TestEqual(counted::live, 2);
			TestEqual(copy.value().value, counted::payload('v'));
			TestEqual(original.value().value, counted::payload('v'));
		}
		// Destroying the copy leaves the original intact.
		TestEqual(counted::live, 1);
		TestEqual(original.value().value, counted::payload('v'));
	}
	// Everything that was constructed has been destroyed exactly once.
	TestEqual(counted::live, 0);
}

Test(result_moved_owns_the_value)
{
	counted::live = 0;
	{
		result<counted, int> source{ counted{counted::payload('m')} };
		result<counted, int> moved{ std::move(source) };

		TestEqual(moved.value().value, counted::payload('m'));
	}
	TestEqual(counted::live, 0);
}

Test(result_converts_to_a_wider_value_type)
{
	result<int, int> narrow{ 5, value_tag{} };
	result<long, int> wide{ narrow };

	TestAssert(bool(wide));
	TestEqual(wide.value(), 5L);

	result<int, int> failed{ 13, error_tag{} };
	result<long, int> wide_error{ failed };

	TestAssert(!wide_error);
	TestEqual(wide_error.error(), 13);
}

Test(assignment_yields_the_assigned_result)
{
	result<long, int> dst{ 0, value_tag{} };
	result<int, int>  src{ 7, value_tag{} };

	auto& ref = (dst = src);

	TestAssert(&ref == &dst);
	TestEqual(dst.value(), 7L);
}
} // namespace aw
