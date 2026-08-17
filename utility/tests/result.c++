#include <aw/utility/result.h>
#include <aw/test/test.h>
#include <aw/test/helpers/counted.h>

TestFile( "result" );

namespace aw {
using test::counted;

namespace {
struct throwing {
	static inline int  live  = 0;
	static inline bool armed = false;
	struct error {};

	throwing()                    { ++live; }
	throwing(throwing const&)     { if (armed) throw error{}; ++live; }
	throwing(throwing&&) noexcept { ++live; }
	throwing& operator=(throwing const&)     = default;
	throwing& operator=(throwing&&) noexcept = default;
	~throwing()                   { --live; }
};
} // namespace

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

/*
 * A rebuild that throws mid-assignment leaves the result valueless rather than
 * destroying a value that was never constructed
 */
Test(result_throwing_assignment_is_safe)
{
	throwing::live  = 0;
	throwing::armed = false;
	{
		result<throwing, int> dst{ value_tag{} };
		result<throwing, int> src{ value_tag{} };
		TestEqual(throwing::live, 2);

		throwing::armed = true;
		TestCatch( throwing::error, dst = src );

		TestAssert(dst.valueless_by_exception());
		TestEqual(throwing::live, 1);
	}
	TestEqual(throwing::live, 0);
}
} // namespace aw
