#include <aw/string/repeat.h>

namespace aw::string {

AW_STRING_EXP
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

} // namespace aw::string
