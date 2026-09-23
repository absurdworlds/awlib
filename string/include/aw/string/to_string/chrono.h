/*
 * Copyright (C) 2026  Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_chrono_to_string_h
#define aw_chrono_to_string_h
#include <chrono>
#include <limits>
#include <numeric>
#include <ratio>
#include <type_traits>
#include <aw/string/to_string.h>
namespace aw {
namespace _impl {
/*!
 * Unit suffix for a duration period, following the list in [time.duration.io].
 * Returns an empty view for periods that have no conventional suffix.
 */
template<typename Period>
constexpr string_view duration_unit()
{
	using namespace std;
	if constexpr (ratio_equal_v<Period, atto>)  return "as";
	if constexpr (ratio_equal_v<Period, femto>) return "fs";
	if constexpr (ratio_equal_v<Period, pico>)  return "ps";
	if constexpr (ratio_equal_v<Period, nano>)  return "ns";
	if constexpr (ratio_equal_v<Period, micro>) return "us";
	if constexpr (ratio_equal_v<Period, milli>) return "ms";
	if constexpr (ratio_equal_v<Period, centi>) return "cs";
	if constexpr (ratio_equal_v<Period, deci>)  return "ds";
	if constexpr (ratio_equal_v<Period, ratio<1>>) return "s";
	if constexpr (ratio_equal_v<Period, deca>)  return "das";
	if constexpr (ratio_equal_v<Period, hecto>) return "hs";
	if constexpr (ratio_equal_v<Period, kilo>)  return "ks";
	if constexpr (ratio_equal_v<Period, mega>)  return "Ms";
	if constexpr (ratio_equal_v<Period, giga>)  return "Gs";
	if constexpr (ratio_equal_v<Period, tera>)  return "Ts";
	if constexpr (ratio_equal_v<Period, peta>)  return "Ps";
	if constexpr (ratio_equal_v<Period, exa>)   return "Es";
	if constexpr (ratio_equal_v<Period, ratio<60>>)    return "min";
	if constexpr (ratio_equal_v<Period, ratio<3600>>)  return "h";
	if constexpr (ratio_equal_v<Period, ratio<86400>>) return "d";
	return {};
}

/*!
 * Check whether a * b is representable in T
 */
template<typename T>
constexpr bool mul_overflows(T a, T b)
{
	if (a == 0 || b == 0)
		return false;
	constexpr T max = std::numeric_limits<T>::max();
	constexpr T min = std::numeric_limits<T>::lowest();
	if (a > 0)
		return b > 0 ? a > max / b : b < min / a;
	return b > 0 ? a < min / b : a < max / b;
}

/*!
 * Write an integer duration whose period has no unit suffix
 * as a fraction of a second: "[6/7]s", or "3s" when it is whole.
 *
 * When the numerator would overflow, the count is written
 * separately: "9223372036854775807*[3/7]s".
 */
template<typename Formatter, typename Rep, typename Period>
void write_duration_ratio(Formatter& fmt, std::chrono::duration<Rep, Period> const& dur)
{
	// TODO: generalise this to std::ratio
	using T = std::common_type_t<Rep, intmax_t>;
	T count = dur.count();
	T num   = Period::num;
	T den   = Period::den;

	if (mul_overflows(count, num)) {
		fmt.convert( count );
		fmt.literal( "*[" );
		fmt.convert( num );
		if (den != 1) {
			fmt.literal( "/" );
			fmt.convert( den );
		}
		fmt.literal( "]s" );
		return;
	}

	num *= count;
	if (den != 1) {
		// |num| can be unrepresentable if num INT64_MIN,
		// so gcd(num, den) would be an UB
		T g = std::gcd( den, num % den );
		num /= g;
		den /= g;
	}

	if (den == 1) {
		fmt.convert( num );
	} else {
		fmt.literal( "[" );
		fmt.convert( num );
		fmt.literal( "/" );
		fmt.convert( den );
		fmt.literal( "]" );
	}
	fmt.literal( "s" );
}
} // namespace _impl

/*!
 * Convert duration to string
 * \return
 *    Tick count followed by the unit suffix, e.g. "1500ms".
 *    Periods without a conventional suffix are converted
 *    to seconds: "3s", "[6/7]s", or "1.500000s" for a
 *    floating-point representation.
 */
template <typename Rep, typename Period>
struct string_converter<std::chrono::duration<Rep, Period>> {
	std::chrono::duration<Rep, Period> const& dur;

	template<typename Formatter>
	std::string operator()( Formatter& fmt ) const
	{
		constexpr auto unit = _impl::duration_unit<Period>();
		if constexpr (!unit.empty()) {
			fmt.convert( dur.count() );
			fmt.literal( unit );
		} else if constexpr (std::is_floating_point_v<Rep>) {
			using seconds = std::chrono::duration<Rep>;
			fmt.convert( std::chrono::duration_cast<seconds>(dur).count() );
			fmt.literal( "s" );
		} else {
			_impl::write_duration_ratio( fmt, dur );
		}
		return fmt;
	}
};
} // namespace aw
#endif//aw_chrono_to_string_h
