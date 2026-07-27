/*
 * Copyright (C) 2016  Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
/*
 * std::string provides the very same search operations since C++98,
 * so it is used here as a reference implementation.
 */
#include <awstd/string_view>

#include <string>

#include "awstd_test.h"

namespace z = awstd;

namespace {
std::string context(std::string const& hay, std::string const& needle)
{
	return " [\"" + hay + "\", \"" + needle + "\"]";
}

std::string context(std::string const& hay, std::string const& needle, size_t pos)
{
	return " [\"" + hay + "\", \"" + needle + "\", " +
	       awstd_test::to_string(pos) + "]";
}

void compare_search(std::string const& hay, std::string const& needle)
{
	z::string_view sv(hay);
	z::string_view nv(needle);

	std::string const ctx = context(hay, needle);

	CheckEqualCtx(hay.find(needle),              sv.find(nv),              ctx);
	CheckEqualCtx(hay.rfind(needle),             sv.rfind(nv),             ctx);
	CheckEqualCtx(hay.find_first_of(needle),     sv.find_first_of(nv),     ctx);
	CheckEqualCtx(hay.find_last_of(needle),      sv.find_last_of(nv),      ctx);
	CheckEqualCtx(hay.find_first_not_of(needle), sv.find_first_not_of(nv), ctx);
	CheckEqualCtx(hay.find_last_not_of(needle),  sv.find_last_not_of(nv),  ctx);

	for (size_t pos = 0; pos <= hay.size() + 1; ++pos) {
		std::string const ctxp = context(hay, needle, pos);

		CheckEqualCtx(hay.find(needle, pos),              sv.find(nv, pos),              ctxp);
		CheckEqualCtx(hay.rfind(needle, pos),             sv.rfind(nv, pos),             ctxp);
		CheckEqualCtx(hay.find_first_of(needle, pos),     sv.find_first_of(nv, pos),     ctxp);
		CheckEqualCtx(hay.find_last_of(needle, pos),      sv.find_last_of(nv, pos),      ctxp);
		CheckEqualCtx(hay.find_first_not_of(needle, pos), sv.find_first_not_of(nv, pos), ctxp);
		CheckEqualCtx(hay.find_last_not_of(needle, pos),  sv.find_last_not_of(nv, pos),  ctxp);
	}
}

void compare_search_char(std::string const& hay, char needle)
{
	z::string_view sv(hay);

	std::string const ctx = context(hay, std::string(1, needle));

	CheckEqualCtx(hay.find(needle),  sv.find(needle),  ctx);
	CheckEqualCtx(hay.rfind(needle), sv.rfind(needle), ctx);

	for (size_t pos = 0; pos <= hay.size() + 1; ++pos) {
		std::string const ctxp = context(hay, std::string(1, needle), pos);

		CheckEqualCtx(hay.find(needle, pos),  sv.find(needle, pos),  ctxp);
		CheckEqualCtx(hay.rfind(needle, pos), sv.rfind(needle, pos), ctxp);
	}
}

void test_search()
{
	char const* haystacks[] = {
		"", "/", "//", "a", "/test/patho/", "test.txt", "..", "aaaa", "abcabc"
	};
	char const* needles[] = {
		"", "/", "//", "a", "path", "/te", "ho/", "x", "abc", "/test/patho/"
	};

	size_t const nh = sizeof(haystacks) / sizeof(haystacks[0]);
	size_t const nn = sizeof(needles) / sizeof(needles[0]);

	for (size_t i = 0; i < nh; ++i) {
		for (size_t j = 0; j < nn; ++j)
			compare_search(haystacks[i], needles[j]);

		compare_search_char(haystacks[i], '/');
		compare_search_char(haystacks[i], 'a');
		compare_search_char(haystacks[i], 'x');
		compare_search_char(haystacks[i], '.');
	}
}

void test_construction()
{
	z::string_view empty;
	Check(empty.empty());
	CheckEqual(empty.size(), size_t(0));

	z::string_view literal("literal");
	CheckEqual(literal.size(), size_t(7));
	CheckEqual(std::string(literal), std::string("literal"));

	char const* ptr = "pointer";
	z::string_view from_ptr(ptr);
	CheckEqual(from_ptr.size(), size_t(7));

	z::string_view sized("sized", 3);
	CheckEqual(sized.size(), size_t(3));
	CheckEqual(std::string(sized), std::string("siz"));

	std::string str("string");
	z::string_view from_str(str);
	CheckEqual(from_str.size(), str.size());
	CheckEqual(std::string(from_str), str);

	z::string_view copy(from_str);
	Check(copy == from_str);

	copy = literal;
	Check(copy == literal);
	Check(copy != from_str);
}

void test_access()
{
	std::string const str("/test/patho/");
	z::string_view sv(str);

	CheckEqual(sv.size(), str.size());
	CheckEqual(sv[0], str[0]);
	CheckEqual(sv[sv.size() - 1], str[str.size() - 1]);

	size_t count = 0;
	for (z::string_view::iterator it = sv.begin(); it != sv.end(); ++it) {
		CheckEqual(*it, str[count]);
		++count;
	}
	CheckEqual(count, str.size());

	CheckEqual(std::string(sv.substr(0)),    str.substr(0));
	CheckEqual(std::string(sv.substr(3, 5)), str.substr(3, 5));
	CheckEqual(std::string(sv.substr(str.size())), str.substr(str.size()));
	CheckEqual(std::string(sv.substr(3, 100)), str.substr(3, 100));

	z::string_view trimmed(str);
	trimmed.remove_prefix(1);
	trimmed.remove_suffix(1);
	CheckEqual(std::string(trimmed), str.substr(1, str.size() - 2));
}

void test_compare()
{
	z::string_view a("abc");
	z::string_view b("abd");
	z::string_view c("abc");

	Check(a == c);
	Check(a != b);
	Check(a < b);
	Check(b > a);
	Check(a <= c);
	Check(a >= c);

	Check(z::string_view("") < a);
	Check(!(a < z::string_view("ab")));
}

void test_print()
{
	std::ostringstream stream;
	stream << z::string_view("printed");
	CheckEqual(stream.str(), std::string("printed"));
}
} // namespace

int main()
{
	test_construction();
	test_access();
	test_compare();
	test_search();
	test_print();

	return awstd_test::result();
}
