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
#include <string_view>

namespace aw {
using std::basic_string_view;
using std::u8string_view;
using std::string_view;
using std::wstring_view;

/*!
 * Create a string_view from a character array.
 *
 * A single trailing null is not part of the view, so that
 * make_string_view("hello").size() == 5. Arrays which are not
 * null-terminated are viewed in full.
 */
template<size_t N>
constexpr string_view make_string_view(char const (&array)[N])
{
	return {array, N > 0 && array[N-1] == '\0' ? N-1 : N};
}
} // namespace aw
#endif//aw_utility_string_view_h
