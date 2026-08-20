#ifndef aw_utility_string_parse_h
#define aw_utility_string_parse_h

#include <aw/types/string_view.h>

#include <charconv>
#include <limits>
#include <optional>
#include <type_traits>

namespace aw::string {
namespace _impl {
/*!
 * Take a base prefix off the front of \a digits: `0b`, `0o`, `0d` or `0x`.
 * Returns 0 and leaves \a digits alone when there is none.
 *
 * \note `0` does not mean octal: `010` is ten, not eight.
 */
inline int take_base_prefix(string_view& digits)
{
	if (digits.size() < 2 || digits[0] != '0')
		return 0;

	int base;
	switch (digits[1]) {
	case 'b': case 'B': base = 2;  break;
	case 'o': case 'O': base = 8;  break;
	case 'd': case 'D': base = 10; break;
	case 'x': case 'X': base = 16; break;
	default: return 0;
	}

	digits.remove_prefix(2);
	return base;
}

//! Parse all of \a s as a number in \a base, or fail.
template<typename T>
bool parse_number(string_view s, T& v, int base)
{
	auto const end = s.data() + s.size();

	T tmp{};
	std::from_chars_result result;
	if constexpr (std::is_integral_v<T>)
		result = std::from_chars(s.data(), end, tmp, base);
	else
		result = std::from_chars(s.data(), end, tmp, base == 16
		                         ? std::chars_format::hex
		                         : std::chars_format::general);

	if (result.ec != std::errc() || result.ptr != end)
		return false;

	v = tmp;
	return true;
}
} // namespace _impl

/*!
 * Parse the whole of \a line into \a v.
 *
 * - Does not strip whitespace.
 * - Does not accept leading whitespace.
 * - Does not accept any trailing characters.
 * - Accepts leading '+' for unsigned numbers, and both '-' and '+' for signed numbers.
 * - Accepts a base prefix after the sign: `0b`, `0o`, `0d` or `0x` for integers,
 *   and `0x` (a hexadecimal float) for floating point numbers.
 * - A number with no prefix is decimal, there is no plain `0` octal prefix, so
 *   `010` is ten rather than eight.
 *
 * \return
 *    `true` if all of \a line was a number, leaving \a v alone otherwise.
 */
template<typename T>
bool try_parse(string_view line, T& v)
{
	bool const positive = line.starts_with('+');
	if (positive)
		// std::from_chars() accepts a leading '-', but not a leading '+'
		line.remove_prefix(1);

	bool const negative = line.starts_with('-');
	if (positive && negative)
		// only the one sign belongs to the number
		return false;

	string_view digits = line;
	if (negative)
		digits.remove_prefix(1);

	int const base = _impl::take_base_prefix(digits);

	// without a base prefix std::from_chars() can read the sign itself
	if (base == 0)
		return _impl::parse_number(line, v, 10);

	if constexpr (std::is_unsigned_v<T>) {
		if (negative)
			return false;
	}

	if constexpr (std::is_integral_v<T>) {
		using U = std::make_unsigned_t<T>;

		U magnitude{};
		if (!_impl::parse_number(digits, magnitude, base))
			return false;

		constexpr U max = std::numeric_limits<T>::max();
		if (negative) {
			// one more value fits below zero than above it
			if (magnitude > U(max + 1))
				return false;
			v = T(U(0) - magnitude);
		} else {
			if (magnitude > max)
				return false;
			v = T(magnitude);
		}
	} else {
		// floating point numbers take no base other than hexadecimal
		if (base != 16)
			return false;

		T magnitude{};
		if (!_impl::parse_number(digits, magnitude, base))
			return false;

		v = negative ? -magnitude : magnitude;
	}

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
