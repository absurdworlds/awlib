#ifndef aw_utility_string_parse_h
#define aw_utility_string_parse_h

#include <aw/types/string_view.h>

#include <charconv>

namespace aw::string {
template<typename T>
bool try_parse(string_view line, T& v)
{
	auto result = std::from_chars(begin(line), end(line), v);
	return result.ec != std::errc();
}

template<typename T>
T parse(string_view line, T default_value = T())
{
	T val;
	if (!try_parse(line, val))
		return default_value;
	return val;
}
} // namespace aw::string

#endif // aw_utility_string_parse_h
