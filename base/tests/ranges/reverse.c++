#include <aw/ranges/reverse.h>
#include <aw/test/test.h>
#include <aw/test/helpers/copy_move_tracker.h>
#include <memory>
#include <vector>

TestFile( "ranges::reverse" );

namespace aw {
namespace {
using tracker = test::copy_move_tracker<int>;

std::vector<tracker> make_tracked()
{
	std::vector<tracker> vec;
	vec.reserve(3);
	for (int i = 0; i < 3; ++i)
		vec.emplace_back(i);
	return vec;
}
} // namespace

Test(reverse_iterates_backwards) {
	std::vector<int> const vec {1, 2, 3, 4};

	std::vector<int> got;
	for (auto val : reverse(vec))
		got.push_back(val);

	std::vector<int> const expect {4, 3, 2, 1};
	TestEqual(got, expect);
}

/*!
 * A temporary is taken over rather than duplicated, so its elements are
 * not copied.
 */
Test(reverse_takes_over_a_temporary) {
	auto rev = reverse(make_tracked());

	std::vector<int> got;
	for (auto const& val : rev) {
		TestEqual(val.n_copies, 0u);
		got.push_back(val.value);
	}

	std::vector<int> const expect {2, 1, 0};
	TestEqual(got, expect);
}

/*!
 * Elements which cannot be copied can still be iterated.
 */
Test(reverse_accepts_move_only_elements) {
	std::vector<std::unique_ptr<int>> vec;
	vec.push_back(std::make_unique<int>(1));
	vec.push_back(std::make_unique<int>(2));

	std::vector<int> got;
	for (auto const& val : reverse(std::move(vec)))
		got.push_back(*val);

	std::vector<int> const expect {2, 1};
	TestEqual(got, expect);
}

/*!
 * An lvalue is referred to, so writes through it reach the original.
 */
Test(reverse_lvalue_kept_by_reference) {
	std::vector<int> vec {1, 2, 3};

	for (auto& val : reverse(vec))
		val += 10;

	std::vector<int> const expect {11, 12, 13};
	TestEqual(vec, expect);
}
} // namespace aw
