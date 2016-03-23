/*
 * Copyright (C) 2016  Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_Archive_base
#define aw_Archive_base
#include <cassert>
#include <utility>
#include <aw/types/types.h>
#include <aw/types/traits/enable_if.h>
#include <aw/types/traits/has_a.h>
#include <aw/types/traits/basic_traits.h>
namespace aw {
namespace arc {
namespace detail {
template <typename T> struct IsContainer : std::false_type{};
} // namespace detail

template<typename T>
constexpr auto IsContainer = detail::IsContainer<T>::value;

template<typename T>
constexpr auto IsPrimitive = is_arithmetic<T> || is_string<T>;

template<typename T>
constexpr auto IsObject = !IsContainer<T> && !IsPrimitive<T> && !is_pointer<T>;
} // namespace arc
} // namespace aw
#endif//aw_Archive_base
