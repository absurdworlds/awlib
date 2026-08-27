#ifndef aw_string_literal_h
#define aw_string_literal_h

#include <aw/types/types.h>
#include <aw/types/string_view.h>

#include <algorithm>

namespace aw {
/*!
 * String literal class for use in template parameters.
 */
template<size_t N>
struct string_literal {
	constexpr string_literal(const char (&str)[N])
	{
		std::copy_n(str, N, value);
	}

	constexpr operator string_view() const
	{
		// -1 because of the zero-terminator
		return string_view(value, N-1);
	}

	char value[N];
};

} // namespace aw

#endif // aw_string_literal_h
