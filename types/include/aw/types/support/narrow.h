#ifndef aw_types_support_narrow_h
#define aw_types_support_narrow_h

#include <type_traits>
#include <utility>
#include <cassert>

namespace aw {
/*!
 * Narrowing cast.
 * Identical to static_cast but makes it easier to grep the code.
 */
template <typename To, typename From>
constexpr To narrow_cast(From&& from) noexcept
{
	return static_cast<To>(std::forward<From>(from));
}

template <typename T, typename U>
constexpr bool same_sign(const T& t, const U& u)
{
	return (t < T{}) == (u < U{});
}

/*!
 * Checked narrowing cast. Inspired by GSL.
 */
template <class To, class From>
	requires std::is_arithmetic_v<To>
constexpr To narrow(From from)
{
	auto to = narrow_cast<To>(from);

	assert(static_cast<From>(to) == from);

	if constexpr(std::is_signed_v<To> != std::is_signed_v<From>)
		assert(same_sign(to, from));

	return to;
}

template <class To, class From>
	requires (!std::is_arithmetic_v<To>)
constexpr To narrow(From from)
{
	auto to = narrow_cast<To>(from);

	assert(static_cast<From>(to) == from);

	return to;
}
} // namespace aw

#endif // aw_types_support_narrow_h
