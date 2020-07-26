#include <aw/algorithm/common_prefix_length.h>
#include <aw/types/string_view.h>
#include <aw/utility/test.h>
#include <vector>
#include <string>

TestFile( "algorithm::common_prefix" );

namespace aw {
Test(common_prefix_length_base_case) {
	std::vector<std::string> strings = {
		"test_1",
		"test_2",
		"test_other"
	};

	auto prefix_length = common_prefix_length(begin(strings), end(strings));
	TestEqual(prefix_length, string_view("test_").size());
}

Test(common_prefix_length_non_matching) {
	std::vector<std::string> strings = {
		"test_1",
		"test_2",
		"test_other",
		"non_matching"
	};

	auto prefix_length = common_prefix_length(begin(strings), end(strings));
	TestEqual(prefix_length, 0);
}

} // namespace aw
