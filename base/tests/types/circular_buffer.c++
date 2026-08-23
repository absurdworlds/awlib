#include <array>
#include <aw/types/containers/circular_buffer.h>

#include <aw/ranges/zip.h>
#include <aw/test/test.h>
#include <aw/test/helpers/lifetime_tracker.h>

TestFile( "aw::circular_buffer" );

namespace aw {
using test::lifetime_tracker;

Test(circular_buf_push_back) {
	circular_buffer<int> buf(3);
	buf.push_back(1);
	buf.push_back(2);
	buf.push_back(3);

	Checks {
		constexpr std::array prot{1,2,3};
		for (auto [e,v] : zip(prot, buf))
			TestEqual(e,v);
	}

	buf.push_back(4);
	Checks {
		constexpr std::array prot{2,3,4};
		for (auto [e,v] : zip(prot, buf))
			TestEqual(e,v);
	}
}						

Test(circular_buf_push_front) {
	circular_buffer<int> buf(3);
	buf.push_front(1);
	buf.push_front(2);
	buf.push_front(3);

	Checks {
		constexpr std::array prot{3,2,1};
		for (auto [e,v] : zip(prot, buf))
			TestEqual(e,v);
	}

	buf.push_front(4);
	Checks {
		constexpr std::array prot{4,3,2};
		for (auto [e,v] : zip(prot, buf))
			TestEqual(e,v);
	}

	buf.push_back(5);
	Checks {
		constexpr std::array prot{3,2,5};
		for (auto [e,v] : zip(prot, buf))
			TestEqual(e,v);
	}
}

Test(circular_buf_size) {
	circular_buffer<int> buf(3);

	Checks {
		TestEqual(buf.size(), size_t(0));
		TestAssert(buf.empty());

		buf.push_back(1);
		TestEqual(buf.size(), size_t(1));
		TestAssert(!buf.empty());

		buf.push_back(2);
		buf.push_back(3);
		TestEqual(buf.size(), size_t(3));
		TestEqual(buf.capacity(), size_t(3));

		// pushing into a full buffer keeps the count at capacity
		// TODO: implement policy: overwrite, drop, throw
		buf.push_back(4);
		TestEqual(buf.size(), size_t(3));

		buf.pop_front();
		TestEqual(buf.size(), size_t(2));

		buf.clear();
		TestEqual(buf.size(), size_t(0));
		TestAssert(buf.empty());
	}
}

Test(circular_buf_copy) {
	circular_buffer<int> a(3);
	a.push_back(1);
	a.push_back(2);
	a.push_back(3);

	circular_buffer<int> b(a);

	Checks {
		TestEqual(b.capacity(), a.capacity());
		TestEqual(b.size(), a.size());
		TestAssert(std::equal(a.begin(), a.end(), b.begin(), b.end()));
	}

	circular_buffer<int> empty(3);
	circular_buffer<int> empty_copy(empty);

	Checks {
		TestAssert(empty_copy.empty());
		TestEqual(empty_copy.size(), size_t(0));
		TestEqual(empty_copy.capacity(), size_t(3));
	}
}

Test(circular_buf_destroys_elements) {
	lifetime_tracker::live = 0;

	Checks {
		{
			circular_buffer<lifetime_tracker> buf(3);
			buf.push_back(lifetime_tracker{});
			buf.push_back(lifetime_tracker{});
			TestEqual(lifetime_tracker::live, 2);

			circular_buffer<lifetime_tracker> copy(buf);
			TestEqual(lifetime_tracker::live, 4);
		}
		TestEqual(lifetime_tracker::live, 0);
	}
}
} // namespace aw
