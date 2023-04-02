#ifndef aw_algorithm_exchange_h
#define aw_algorithm_exchange_h

#include <utility>

namespace aw {

using std::exchange;

/*!
 * \brief Moves values to the left in a chain-like manner.
 */
template <class T, class U, class... Us>
void shift_left(T&& first, U&& second, Us&&... rest)
{
	if constexpr(sizeof...(Us) == 0)
		first = std::forward<U>(second);
	else {
		first = std::move(second);
		shift_left(second, std::forward<Us>(rest)...);
	}
}

namespace _impl {
template <class T, class U, class... Us>
void shift_move_right(T&& first, U&& second, Us&&... rest)
{
	if constexpr(sizeof...(Us) > 0)
		shift_move_right(second, std::forward<Us>(rest)...);
	second = std::move(first);
}
} // namespace _impl

/*!
 * \brief Moves values to the right in a chain-like manner.
 */
template <class T, class U, class... Us>
void shift_right(T&& first, U&& second, Us&&... rest)
{
	if constexpr(sizeof...(Us) > 0)
		_impl::shift_move_right(second, std::forward<Us>(rest)...);
	second = std::forward<T>(first);
}

/*!
 * \brief Swaps the values of multiple objects in a chain-like manner.
 * The \a first gets the value of the \a second and so on.
 *
 * \return The original value of the first object.
 */
template <class T, class U, class... Us>
constexpr auto exchange_chain(T& first, U&& second, Us&&... rest) -> T
{
	auto old_first = std::move(first);
	shift_left(first, std::forward<U>(second), std::forward<Us>(rest)...);
	return old_first;
}

/*!
 * \brief Swaps values of multiple objects in circle counter-clockwise.
 *
 * The \a first gets the value of the \a second and so on.
 * The last object gets the value of the \a first.
 *
 * In other words, if you place \a first at 12 o'clock, second at 1 o'clock
 * and so on, it performs a counter-clockwise shift.
 */
template <class T, class U, class... Us>
constexpr void rotate_left(T&& first, U&& second, Us&&... rest)
{
	auto old_first = exchange(first, std::forward<U>(second));

	shift_left(second, std::forward<Us>(rest)..., std::move(old_first));
}

/*!
 * \brief Swaps values of multiple objects in circle clockwise.
 */
template <class T, class U, class... Us>
constexpr void rotate_right(T&& first, U&& second, Us&&... rest)
{
	auto old_first = std::move(first);

	shift_right(second, rest..., first);

	second = std::move(old_first);
}
} // namespace aw


#endif // aw_algorithm_exchange_h
