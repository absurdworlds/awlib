#include <array>
#include <aw/types/containers/circular_buffer.h>

#include <aw/utility/ranges/zip.h>
#include <aw/test/test.h>

TestFile( "aw::circular_buffer" );

namespace aw {
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
} // namespace aw
