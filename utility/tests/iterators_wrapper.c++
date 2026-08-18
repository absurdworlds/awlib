#include <aw/utility/iterators/wrapper.h>
#include <aw/test/test.h>
#include <iterator>
#include <memory>
#include <vector>

TestFile( "iterators::wrapper" );

namespace aw {
namespace {
struct thing {
	int value;
};

//! Hands out the pointer held by a smart pointer, without copying the owner
struct to_pointer {
	thing* operator()(std::unique_ptr<thing> const& ptr) const
	{
		return ptr.get();
	}
};

using owners           = std::vector<std::unique_ptr<thing>>;
using pointer_iterator = iter::wrapper<owners::const_iterator, thing*, to_pointer>;
} // namespace

static_assert(std::input_iterator<pointer_iterator>);
static_assert(std::is_same_v<std::iter_reference_t<pointer_iterator>, thing*>);
static_assert(std::is_same_v<std::iterator_traits<pointer_iterator>::iterator_category,
                             std::input_iterator_tag>);

/*!
 * A range of move-only elements can be read through as a range of plain
 * pointers to them
 */
Test(wrapper_views_move_only_elements)
{
	owners vec;
	vec.push_back(std::make_unique<thing>(thing{1}));
	vec.push_back(std::make_unique<thing>(thing{2}));

	auto it   = pointer_iterator{vec.begin()};
	auto last = pointer_iterator{vec.end()};

	std::vector<int> got;
	while (it != last)
		got.push_back((*it++)->value);

	std::vector<int> const expect {1, 2};
	TestEqual(got, expect);
}

/*!
 * The wrapped range's elements are not modified
 */
Test(wrapper_leaves_the_owners_alone)
{
	owners vec;
	vec.push_back(std::make_unique<thing>(thing{7}));

	auto it = pointer_iterator{vec.begin()};
	TestEqual((*it)->value, 7);
	TestAssert(vec.front() != nullptr);
}
} // namespace aw
