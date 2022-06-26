#include <aw/algorithm/split.h>
#include <aw/types/string_view.h>

#include <aw/test/test.h>

TestFile( "algorithm::split" );

namespace aw {
Test(split_basic) {
	auto test1 = [] (std::string const& s, std::vector<std::string> const& e) {
		std::vector<std::string> v;
		split(begin(s), end(s), '/', [&] (auto a, auto b) { v.emplace_back(a,b); });
		TestEqual(v,e);
	};

	Checks {
		test1("", {});
		test1("/", {});
		test1("/a", {"a"});
		test1("a/", {"a"});
		test1("/a/", {"a"});
		test1("a/b/", {"a", "b"});
		test1("/b/c", {"b", "c"});
		test1("a/b/c", {"a","b","c"});
	}
}

Test(cut_basic) {
	auto test2 = [] (std::string const& s, std::vector<std::string> const& e) {
		std::vector<std::string> v;
		cut(begin(s), end(s), '/', [&] (auto a, auto b) { v.emplace_back(a,b); });
		TestEqual(v,e);
	};

	Checks {
		test2("", {""});
		test2("/", {"",""});
		test2("/a", {"","a"});
		test2("a/", {"a",""});
		test2("/a/", {"","a",""});
		test2("a/b/", {"a", "b",""});
		test2("/b/c", {"","b", "c"});
		test2("a/b/c", {"a","b","c"});
	}
}
} // namespace aw
