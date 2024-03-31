#ifndef aw_string_repeat_h
#define aw_string_repeat_h

#include <aw/string/export.h>

#include <cstring>
#include <string>

namespace aw::string {
/*!
 * Repeat the string to extend its length to total_size.
 */
AW_STRING_EXP
std::string extend(std::string_view str, size_t total_size);

/*!
 * Repeat the string n times.
 */
inline std::string repeat(std::string_view str, size_t n)
{
	return extend(str, str.size() * n);
}

namespace operators {
inline std::string operator*(std::string_view str, size_t n)
{
	return repeat(str,n);
}
} // namespace operators
} // namespace aw::string

#endif // aw_string_repeat_h
