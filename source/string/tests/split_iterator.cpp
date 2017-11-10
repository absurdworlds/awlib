#include <aw/utility/string/lazy_split.h>
#include <aw/utility/ranges/paired.h>
#include <aw/utility/test.h>

TestFile( "string::split_iterator" );

namespace aw {
namespace string {
Test(empty) {
	for (auto s : split_by_iterator("abcd", ""))
		TestEqual(s, "abcd");
	for (auto s : split_by_iterator("", "/"))
		TestAssert(false);
	for (auto s : split_iterator("", "/"))
		TestAssert(false);
	for (auto s : cut_iterator("", "/"))
		TestEqual(s, ""); // TODO: TestOnce
}

Test(split_iter_basic) {
	std::vector<string_view> result[6];
	std::vector<string_view> expected[6] = {
		{"x","y","z","w"},
		{"xx","yy","zz","ww"},
		{"a","b","c","d"},
		{"a","b","c","d"},
		{"", "", "aa", "", "bb","cc", "", "", "dd", "", "", ""},
		{"aa", "bb","cc", "dd"},
	};

	for (auto s : split_by_iterator("x/y/z/w", "/"))
		result[0].push_back(s);
	for (auto s : split_by_iterator("//xx//yy/zz///ww///", "/"))
		result[1].push_back(s);

	for (auto s : split_iterator("a/b/c/d", "/"))
		result[2].push_back(s);
	for (auto s : split_iterator("a//b//c//d////", "//"))
		result[3].push_back(s);

	for (auto s : cut_iterator("//aa//bb/cc///dd///", "/"))
		result[4].push_back(s);
	for (auto s : split_iterator("//aa//bb/cc///dd///", "/"))
		result[5].push_back(s);

	for (auto&& [r, e] : aw::paired(result, expected))
		TestEqual(r, e);
}
} // namespace string
} // namespace aw
