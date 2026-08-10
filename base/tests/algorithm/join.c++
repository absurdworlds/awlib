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
		auto a = join_into(begin(strs), end(strs),  std::string(), delim, adder1);
		auto b = join_into(begin(strs), end(strs),  std::string(), delim);
		TestEqualV(a,b);
		TestEqual(a, "-A-B-C");
		TestEqual(join_into(begin(strs), end(strs), std::string("XXX"), delim, adder1), "XXX-A-B-C");

		auto c = join(begin(strs), end(strs), std::string(delim), adder1);
		auto d = join(begin(strs), end(strs), std::string(delim));
		TestEqualV(c,d);
		TestEqual(c, "A-B-C");
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

Test(join_empty_delim) {
	std::vector<std::string> strs {"A", "B", "C"};
	string_view delim;
	Checks {
		auto v = join(begin(strs), end(strs), delim);
		TestEqual(v, "ABC");
	}
}

Test(join_empty_elements) {
	std::vector<std::string> strs {"", "", ""};
	string_view delim1{"-"};
	string_view delim2;
	Checks {
		auto v = join(begin(strs), end(strs), delim1);
		TestEqual(v, "--");
	}

	Checks {
		auto v = join(begin(strs), end(strs), delim2);
		TestEqual(v, "");
	}
}

Test(join_one_element) {
	std::vector<std::string> strs{"A"};
	string_view delim1{"-"};
	Checks {
		auto v = join(begin(strs), end(strs), delim1);
		TestEqual(v, "A");
	}
}

Test(join_empty_set) {
	std::vector<std::string> strs;
	string_view delim1{"-"};
	Checks {
		auto v = join(begin(strs), end(strs), delim1);
		TestEqual(v, "");
	}
}
} // namespace aw
