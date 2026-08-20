#include <aw/utility/result.h>
#include <aw/test/test.h>
#include <aw/test/helpers/lifetime_tracker.h>

TestFile( "result" );

namespace aw {
using test::lifetime_tracker;

namespace {
struct throwing {
	static inline int  live  = 0;
	static inline bool armed = false;
	struct error {};

	throwing(int id = 0) : id{id}          { ++live; }
	throwing(throwing const& other)        { if (armed) throw error{}; id = other.id; ++live; }
	throwing(throwing&& other) noexcept    { id = other.id; ++live; }
	throwing& operator=(throwing const&)     = default;
	throwing& operator=(throwing&&) noexcept = default;
	~throwing()                            { --live; }

	int id;
};
} // namespace

static_assert(std::is_nothrow_move_assignable_v<result<lifetime_tracker, int>>);

Test(result_basic_test)
{
	result<lifetime_tracker, int> val{ lifetime_tracker{lifetime_tracker::payload('a')} };
	result<lifetime_tracker, int> err{ 42, error_tag{} };

	TestAssert(bool(val));
	TestAssert(!err);
	TestEqual(val.value().value, lifetime_tracker::payload('a'));
	TestEqual(err.error(), 42);
}

Test(result_copy_owns_an_independent_value)
{
	lifetime_tracker::live = 0;
	{
		result<lifetime_tracker, int> original{ lifetime_tracker{lifetime_tracker::payload('v')} };
		TestEqual(lifetime_tracker::live, 1);
		{
			result<lifetime_tracker, int> copy{ original };
			// Both results now hold a live value of their own.
			TestEqual(lifetime_tracker::live, 2);
			TestEqual(copy.value().value, lifetime_tracker::payload('v'));
			TestEqual(original.value().value, lifetime_tracker::payload('v'));
		}
		// Destroying the copy leaves the original intact.
		TestEqual(lifetime_tracker::live, 1);
		TestEqual(original.value().value, lifetime_tracker::payload('v'));
	}
	// Everything that was constructed has been destroyed exactly once.
	TestEqual(lifetime_tracker::live, 0);
}

Test(result_moved_owns_the_value)
{
	lifetime_tracker::live = 0;
	{
		result<lifetime_tracker, int> source{ lifetime_tracker{lifetime_tracker::payload('m')} };
		result<lifetime_tracker, int> moved{ std::move(source) };

		TestEqual(moved.value().value, lifetime_tracker::payload('m'));
	}
	TestEqual(lifetime_tracker::live, 0);
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
 * An assignment whose copy throws leaves the target holding the value it had
 * before, and destroys nothing twice.
 */
Test(result_throwing_assignment_is_safe)
{
	throwing::live  = 0;
	throwing::armed = false;
	{
		result<throwing, int> dst{ value_tag{}, 1 };
		result<throwing, int> src{ value_tag{}, 2 };
		TestEqual(throwing::live, 2);

		throwing::armed = true;
		TestCatch( throwing::error, dst = src );
		throwing::armed = false;

		// dst kept its original value; nothing was destroyed or leaked.
		TestEqual(dst.value().id, 1);
		TestEqual(throwing::live, 2);
	}
	TestEqual(throwing::live, 0);
}
} // namespace aw
