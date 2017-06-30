/*
 * Copyright (C) 2016  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_iterators_proxy_h
#define aw_iterators_proxy_h
namespace aw {
namespace iter {
/*!
 * Helper class to return a value from overloaded operator->()
 *
 * Example:
 *
 * \code
 * iter::proxy<string_view> operator->()
 * {
 *     return { string_view{ begin + pos1, begin + pos2 } };
 * }
 * \endcode
 */
template <typename T>
struct proxy {
	T _temp;

	constexpr T* operator->()
	{
		return &_temp;
	}

	constexpr T const* operator->() const
	{
		return &_temp;
	}
};
} // namespace iter
} // namespace aw
#endif//aw_IteratorWrapper_h
