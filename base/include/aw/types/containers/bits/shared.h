/*
 * Copyright (C) 2016  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_containers_shared
#define aw_containers_shared
#include <aw/types/traits/iterator.h>
#include <memory>
namespace aw {
namespace _impl {
template<typename InputIt, typename ForwardIt>
ForwardIt try_uninit_move(InputIt begin, InputIt end, ForwardIt output)
{
	using T = typename std::iterator_traits<InputIt>::value_type;
	static_assert(std::is_nothrow_move_constructible<T>::value ||
	              std::is_copy_constructible<T>::value,
	              "T must be nothrow move constructible or copy constructible, "
		      "otherwise elements can't be relocated safely.");

	if constexpr(std::is_nothrow_move_constructible_v<T>)
		return std::uninitialized_move(begin, end, output);
	else
		return std::uninitialized_copy(begin, end, output);

}
} // namespace _impl
} // namespace aw
#endif//aw_containers_shared
