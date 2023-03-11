/*
 * Copyright (C) 2023  Hudd <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_functional_rank_h
#define aw_functional_rank_h

#include <aw/types/types.h>

namespace aw {

/**
 * An overload tag rank to disambiguate template overloads.
 * The higher the rank, the more priority overload has. When
 * calling an overload, pass the highest possible rank tag.
 *
 * Example usage:
 * \code{cpp}
 * template<typename T>
 * auto foo_impl(T,rank_tag<1>) -> void_t<decltype(bar(T))>;
 *
 * template<typename T>
 * void foo_impl(T,rank_tag<0>);
 *
 * template<typename T>
 * void foo_impl(T t)
 * {
 *	foo_impl(t, rank_tag<1>);
 * }
 * \endcode
 */
template<size_t N>
struct rank_tag : rank_tag<N-1> {};

template<>
struct rank_tag<0> {};


} // namespace aw

#endif // aw_functional_rank_h
