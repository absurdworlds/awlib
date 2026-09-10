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

	Checks {
		auto a = join_into(begin(strs), end(strs),  std::string(), delim, adder1);
		auto b = join_into(begin(strs), end(strs),  std::string(), delim);
		TestEqualV(a,b);
		TestEqual(a, "-A-B-C");
		TestEqual(join_into(begin(strs), end(strs), std::string("XXX"), delim, adder1), "XXX-A-B-C");

		auto c = join(begin(strs), end(strs), delim, adder1);
		auto d = join(begin(strs), end(strs), std::string(delim));
		TestEqualV(c,d);
		TestEqual(c, "A-B-C");
	}

	auto adder2 = [] (std::string& s, std::string const& v) {
		s.append(v);
		return s;
	};

	auto adder3 = [] (std::string& s, auto const& v) {
		s.append(v);
		return s;
	};

	Checks {
		std::string_view const result = "A-B-C";

		TestEqual( join(begin(strs), end(strs), std::string(delim), adder1), result );
		TestEqual( join(begin(strs), end(strs), std::string(delim), adder2), result );
		TestEqual( join(begin(strs), end(strs), std::string(delim), adder3), result );

		TestEqual( join(begin(strs), end(strs), delim, adder1), result );
		//TestEqual( join(begin(strs), end(strs), delim, adder2), result ); -- should not compile
		TestEqual( join(begin(strs), end(strs), delim, adder3), result );
	}
}

Test(join_compile_test_with_different_types) {
	std::vector<std::string> strs {"A", "B", "C"};
	std::vector<std::string_view> views {"A", "B", "C"};
	std::string delim{"-"};
	Checks {
		auto v1 = join(begin(strs), end(strs), delim);
		auto v2 = join<std::string>(begin(views), end(views), delim);
		TestEqual(v1, "A-B-C");
		TestEqual(v1, v2);
	}
}

Test(join_compile_test_with_primitive_delim) {
	std::vector<std::string> strs {"A", "B", "C"};
	char const delim{'-'};
	Checks {
		auto v1 = join(begin(strs), end(strs), delim);
		TestEqual(v1, "A-B-C");
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
