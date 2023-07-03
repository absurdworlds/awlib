#ifndef aw_string_repeat_h
#define aw_string_repeat_h

#include <cstring>
#include <string>

namespace aw::string {
/*!
 * Repeat the string to extend its length to total_size.
 */
std::string extend(std::string_view str, size_t total_size)
{
	if (total_size == 0)
		return {};

	std::string result(str);
	size_t size = result.size();

	result.resize(total_size);

	if (total_size < str.size())
		return result;

	auto* p = result.data();

	while (size*2 < total_size) {
		std::memcpy( p+size, p, size );
		size*=2;
	}

	if (size < total_size)
		std::memcpy( p+size, p, total_size - size );

	return result;
}

/*!
 * Repeat the string n times.
 */
std::string repeat(std::string_view str, size_t n)
{
	return extend(str, str.size() * n);
}

namespace operators {
std::string operator*(std::string_view str, size_t n)
{
	return repeat(str,n);
}
} // namespace operators
} // namespace aw::string

#endif // aw_string_repeat_h
