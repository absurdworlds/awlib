#include <aw/utility/string/parser_helpers.h>
#include <aw/test/test.h>

TestFile( "string::parser_helpers" );

namespace aw {
namespace {
size_t find(string_view s)
{
	return find_non_escaped_char(s, ';', '\\');
}
} // namespace

/*!
 * The first delimiter is reported
 */
Test(find_non_escaped_plain) {
	Checks {
		TestEqual(find(R"(a;b)"), size_t(1));
		TestEqual(find(R"(;ab)"), size_t(0));
		TestEqual(find(R"(ab;)"), size_t(2));

		TestEqual(find(R"(a;b;)"), size_t(1));
		TestEqual(find(R"(;ab;)"), size_t(0));
		TestEqual(find(R"(ab;;)"), size_t(2));

		TestEqual(find(R"(abc)"), string_view::npos);
		TestEqual(find(R"()"),    string_view::npos);
	}
}

/*!
 * The search carries on past the escaped delimiter
 */
Test(find_non_escaped_skips_escaped) {
	Checks {
		TestEqual(find(R"(a\;b)"),   string_view::npos);
		TestEqual(find(R"(a\;b;c)"), size_t(4));
		TestEqual(find(R"(\;;)"),    size_t(2));

		// an escape with nothing after it escapes nothing
		TestEqual(find(R"(ab\)"), string_view::npos);
	}
}

/*!
 * An escape can itself be escaped, and then it does not escape the
 * delimiter which follows.
 */
Test(find_non_escaped_escaped_escape) {
	Checks {
		// two escapes: they cancel, so the delimiter stands
		TestEqual(find(R"(a\\;b)"),     size_t(3));
		// three: the last one escapes the delimiter
		TestEqual(find(R"(a\\\;b)"),    string_view::npos);
		// four: they pair up again
		TestEqual(find(R"(a\\\\;b)"),   size_t(5));
	}
}

/*!
 * The iterator form reports the same positions as the index-based
 * version, and the range end when the delimiter wasn't found.
 */
Test(find_non_escaped_iterators) {
	Checks {
		string_view const s = R"(a\;b;c)";
		auto it = find_non_escaped_char(s.begin(), s.end(), ';', '\\');
		TestEqual(size_t(it - s.begin()), size_t(4));

		string_view const none = R"(a\;b)";
		auto missing = find_non_escaped_char(none.begin(), none.end(), ';', '\\');
		TestAssert(missing == none.end());
	}
}
} // namespace aw
