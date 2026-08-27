#include <vector>
#include <aw/types/string_view.h>
#include <aw/algorithm/join.h>
#include <aw/test/test.h>

TestFile( "algorithm::join" );

namespace aw {
Test(join_compile_test) {
	std::vector<std::string> strs {"A", "B", "C"};
	string_view delim{"-"};

	auto adder1 = [] (std::string& s, string_view v) {
		s.append(v);
		return s;
	};

	auto adder2 = [] (std::string& s, std::string const& v) {
		s.append(v);
		return s;
	};

	Checks {
		auto a = join(begin(strs), end(strs),  std::string(), delim, adder1);
		auto b = join(begin(strs), end(strs),  std::string(), delim);
		auto c = join(begin(strs), end(strs), (std::string)delim, adder1);
		auto d = join(begin(strs), end(strs), (std::string)delim);
		TestEqualV(a,b);
		TestEqualV(c,d);
	}
}

Test(join_compile_test_with_different_types) {

	Checks {
		std::vector<std::string_view> strs {"A", "B", "C"};
		std::string delim{"-"};
		auto v = join(begin(strs), end(strs), delim);
		TestEqual(v, "A-B-C");
	}
}
} // namespace aw
