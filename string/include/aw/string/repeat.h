#ifndef aw_string_repeat_h
#define aw_string_repeat_h

#include <aw/string/export.h>

#include <cassert>
#include <cstring>
#include <limits>
#include <stdexcept>
#include <string>

namespace aw::string {
/*!
 * Repeat the string to extend its length to total_size.
 */
AW_STRING_EXP
std::string extend(std::string_view str, size_t total_size);

namespace _impl {
inline void length_error()
{
#if __cpp_exceptions
	throw std::length_error("aw::string::repeat");
#else
	assert(!"length_error");
#endif
}
} // namespace _impl

/*!
 * Repeat the string n times.
 */
inline std::string repeat(std::string_view str, size_t n)
{
	auto const size = str.size();
	if (size != 0 && n > std::numeric_limits<size_t>::max() / size)
		_impl::length_error();

	return extend(str, size * n);
}

namespace operators {
inline std::string operator*(std::string_view str, size_t n)
{
	return repeat(str,n);
}
} // namespace operators
} // namespace aw::string

#endif // aw_string_repeat_h
