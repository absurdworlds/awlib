/*
 * Copyright (C) 2024  Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
/*
 * A tiny test harness: awlib's own one requires a recent C++ standard,
 * which is exactly what awstd is not built with.
 */
#ifndef awstd_test_h
#define awstd_test_h
#include <iostream>
#include <sstream>
#include <string>

namespace awstd_test {

inline int& failure_count()
{
	static int count = 0;
	return count;
}

template<typename T>
std::string to_string(T const& value)
{
	std::ostringstream stream;
	stream << value;
	return stream.str();
}

inline void fail(std::string const& message, char const* file, int line)
{
	std::cerr << file << ':' << line << ": " << message << '\n';
	++failure_count();
}

inline void check(bool result, std::string const& expr, char const* file, int line)
{
	if (!result)
		fail("check failed: " + expr, file, line);
}

template<typename T, typename U>
void check_equal(T const& a, U const& b,
                 std::string const& expr_a, std::string const& expr_b,
                 char const* file, int line)
{
	if (!(a == b)) {
		fail("check failed: " + expr_a + " == " + expr_b +
		     " (" + to_string(a) + " != " + to_string(b) + ")", file, line);
	}
}

inline int result()
{
	if (failure_count() != 0)
		std::cerr << failure_count() << " check(s) failed\n";
	return failure_count() != 0;
}

} // namespace awstd_test

#define Check(expr) \
	::awstd_test::check((expr), #expr, __FILE__, __LINE__)

#define CheckEqual(a, b) \
	::awstd_test::check_equal((a), (b), #a, #b, __FILE__, __LINE__)

//! Same as CheckEqual, but appends \a ctx to the reported expressions
#define CheckEqualCtx(a, b, ctx) \
	::awstd_test::check_equal((a), (b), std::string(#a) + (ctx), \
	                          std::string(#b) + (ctx), __FILE__, __LINE__)

#endif//awstd_test_h
