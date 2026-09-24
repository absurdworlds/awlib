#include <aw/functional/overload.h>
#include <aw/functional/rank.h>
#include <aw/functional/trivial.h>
#include <aw/functional/wrapper.h>
#include <aw/types/string_view.h>
#include <aw/test/test.h>
#include <vector>
#include <memory>
#include <algorithm>
#include <set>
#include <string>
#include <type_traits>

TestFile( "functional" );

namespace aw {
namespace {
int wrapper_calls = 0;
void count_call(int*) { ++wrapper_calls; }

template<typename T>
auto rank_pick(T const& t, rank_tag<1>) -> decltype(t.size(), 1) { return 1; }

template<typename T>
int rank_pick(T const&, rank_tag<0>) { return 0; }
} // namespace

//! Overload dispatches the call to the best-matching lambda.
Test(overload_dispatch)
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

//! Captured state of each lambda is kept in the combined functor.
Test(overload_keeps_captures)
{
	const int base = 10;
	auto func = overload(
		[base] (int x) { return base + x; },
		[] (string_view s) { return int(s.size()); }
	);

	using namespace std::string_view_literals;
	TestEqual(func(5), 15);
	TestEqual(func("abc"sv), 3);
}

//! An overload can be used as a transparent comparator
Test(overload_transparent_comparator)
{
	auto less = [] (string_view a, string_view b) { return a < b; };
	std::set<std::string, overload<decltype(less)>> set{ "a", "b", "c" };

	using namespace std::string_view_literals;
	TestAssert(set.find("b"sv) != set.end());
	TestAssert(set.find("d"sv) == set.end());
}

//! true_func and false_func accept any arguments and return a fixed value.
Test(trivial_predicates)
{
	static_assert(true_func{}(1, "x", nullptr));
	static_assert(!false_func{}(1, "x", nullptr));

	TestAssert(true_func{}());
	TestAssert(true_func{}(1, "x", nullptr));
	TestAssert(!false_func{}());
	TestAssert(!false_func{}(1, "x", nullptr));

	std::vector vec{1, 2, 3, 4, 5};

	auto it1 = std::find_if(begin(vec), end(vec), false_func{});
	auto it2 = std::find_if(begin(vec), end(vec), true_func{});
	TestAssert(it1 == end(vec));
	TestAssert(it2 == begin(vec));
}

//! A function_wrapper works as a unique_ptr deleter, called once on reset.
Test(wrapper_deleter)
{
	wrapper_calls = 0;
	int x = 0;
	std::unique_ptr<int, function_wrapper<count_call>> ptr{ &x };
	TestEqual(wrapper_calls, 0);
	ptr.reset();
	TestEqual(wrapper_calls, 1);
}

//! A higher rank tag converts to every lower one, and the highest rank
//! wins in the overload resolution.
Test(rank_tag_prefers_higher)
{
	static_assert(std::is_base_of_v<rank_tag<0>, rank_tag<2>>);
	TestEqual(rank_pick(std::string{}, rank_tag<1>{}), 1);
	TestEqual(rank_pick(5, rank_tag<1>{}), 0);
}
} // namespace aw
