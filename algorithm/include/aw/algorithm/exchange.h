#ifndef aw_algorithm_exchange_h
#define aw_algorithm_exchange_h

#include <utility>

namespace aw {

using std::exchange;

/*!
 * \brief Swaps the values of multiple objects in a chain-like manner.
 * The \a first gets the value of the \a second and so on.
 *
 * \return The original value of the first object.
 */
template <class T, class U, class... Us>
constexpr auto exchange_chain(T& first, U&& second, Us&&... rest) -> T
{
	if constexpr (sizeof...(Us) == 0)
		return exchange(first, std::forward<U>(second));
	else
		return exchange(first, exchange_chain(second, std::forward<Us>(rest)...));
}

/*!
 * \brief Swaps values of multiple objects in circle.
 * The \a first gets the value of the \a second and so on.
 * The last object gets the value of the \a first.
 */
template <class T, class U, class... Us>
constexpr void exchange_circle(T&& first, U&& second, Us&&... rest)
{
	static_assert(sizeof...(Us) > 0);

	auto old_first = std::exchange(first, std::forward<U>(second));

	exchange_chain(second, rest..., std::move(old_first));
}

} // namespace aw


#endif // aw_algorithm_exchange_h
