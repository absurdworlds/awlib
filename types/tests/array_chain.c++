#include <aw/types/containers/array_chain.h>

#include <aw/test/test.h>
#include <aw/test/helpers/lifetime_tracker.h>

TestFile( "aw::array_chain" );

namespace aw {
using test::lifetime_tracker;

Test(array_chain_push_pop) {
	array_chain<int> c;

	Checks {
		TestEqual(c.size(), size_t(0));

		for (int i = 0; i < 10; ++i)
			c.push_back(i);

		TestEqual(c.size(), size_t(10));
		TestEqual(c[0], 0);
		TestEqual(c[9], 9);

		c.pop_back();
		TestEqual(c.size(), size_t(9));
		TestEqual(c[8], 8);
	}
}

Test(array_chain_pop_back_destroys_last) {
	lifetime_tracker::live = 0;

	Checks {
		{
			array_chain<lifetime_tracker> c;
			c.push_back(lifetime_tracker{lifetime_tracker::payload('a')});
			TestEqual(lifetime_tracker::live, 1);

			c.pop_back();
			TestEqual(lifetime_tracker::live, 0);
			TestEqual(c.size(), size_t(0));
		}
		TestEqual(lifetime_tracker::live, 0);
	}
}

Test(array_chain_pop_back_on_block_boundary) {
	lifetime_tracker::live = 0;

	Checks {
		array_chain<lifetime_tracker> c;

		const auto block = array_chain<lifetime_tracker>::block_size;
		for (size_t i = 0; i < block; ++i)
			c.push_back(lifetime_tracker{lifetime_tracker::payload('b')});

		TestEqual(c.size(), block);
		TestEqual(size_t(lifetime_tracker::live), block);

		c.pop_back();
		TestEqual(c.size(), block - 1);
		TestEqual(size_t(lifetime_tracker::live), block - 1);

		// the remaining elements are intact
		bool intact = true;
		for (size_t i = 0; i < c.size(); ++i)
			intact &= (c[i].value == lifetime_tracker::payload('b'));
		TestAssert(intact);

		while (c.size() > 0)
			c.pop_back();

		TestEqual(lifetime_tracker::live, 0);
	}
}
} // namespace aw
