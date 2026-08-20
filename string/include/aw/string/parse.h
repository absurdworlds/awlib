#ifndef aw_utility_string_parse_h
#define aw_utility_string_parse_h

#include <aw/types/string_view.h>

#include <charconv>
#include <optional>

namespace aw::string {
/*!
 * Parse the whole of \a line into \a v.
 *
 * - Does not strip whitespace.
 * - Does not accept leading whitespace.
 * - Does not accept 0x suffixes.
 * - Does not accept any trailing characters.
 * - Accepts leading '+' for unsigned numbers, and both '-' and '+' for signed numbers
 *
 * \return
 *    `true` if all of \a line was a number, leaving \a v alone otherwise.
 */
template<typename T>
bool try_parse(string_view line, T& v)
{
	// std::from_chars() accepts a leading '-', but not a leading '+'
	if (line.starts_with('+'))
		line.remove_prefix(1);

	auto const end = line.data() + line.size();

	T tmp{};
	auto result = std::from_chars(line.data(), end, tmp);
	if (result.ec != std::errc() || result.ptr != end)
		return false;

	v = tmp;
	return true;
}

template<typename T>
std::optional<T> parse(string_view line)
{
	T val;
	if (!try_parse(line, val))
		return {};
	return val;
}

template<typename T>
T parse(string_view line, T default_value)
{
	return parse<T>(line).value_or(default_value);
}
} // namespace aw::string

#endif // aw_utility_string_parse_h
