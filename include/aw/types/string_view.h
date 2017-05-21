/*
 * Copyright (C) 2016  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_utility_string_view_h
#define aw_utility_string_view_h
#if __has_include(<string_view>)
#include <string_view>
namespace aw {
using std::basic_string_view;
using std::string_view;
using std::wstring_view;
} // namespace aw;
#elif __has_include(<experimental/string_view>)
#include <experimental/string_view>
namespace aw {
using std::experimental::basic_string_view;
using std::experimental::string_view;
using std::experimental::wstring_view;
} // namespace aw;
#endif

namespace aw {
template<size_t N>
constexpr string_view make_string_view(char const (&array)[N])
{
	return {array, N};
}

namespace string_literals {
using namespace std::string_literals;
using namespace std::string_view_literals;
} // namespace string_literals
} // namespace aw
#endif//aw_utility_string_view_h
