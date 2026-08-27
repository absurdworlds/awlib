#include <aw/ranges/value_range.h>
#include <aw/ranges/reverse.h>
#include <aw/test/test.h>
#include <iterator>
#include <vector>

TestFile( "ranges::value_range" );

namespace aw {
static_assert(std::bidirectional_iterator<value_range<int>::iterator>);

Test(value_range_forward)
{
	std::vector<int> seen;
	for (auto v : range(1, 5))
		seen.push_back(v);

	std::vector<int> const expected{ 1, 2, 3, 4 };
	TestEqual(seen, expected);
}

Test(value_range_counting_from_zero)
{
	std::vector<int> seen;
	for (auto v : range(4))
		seen.push_back(v);

	std::vector<int> const expected{ 0, 1, 2, 3 };
	TestEqual(seen, expected);
}

Test(value_range_backward)
{
	std::vector<int> seen;
	for (auto v : reverse(range(1, 5)))
		seen.push_back(v);

	std::vector<int> const expected{ 4, 3, 2, 1 };
	TestEqual(seen, expected);
}
} // namespace aw
