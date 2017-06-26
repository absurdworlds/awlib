/*
 * Copyright (C) 2016  Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_traits_is_smart_pointer_h
#define aw_traits_is_smart_pointer_h
#include <memory>
#include <aw/types/traits/basic_traits.h>

namespace aw {
template<typename T>
constexpr bool is_smart_pointer = false;
template<typename T>
constexpr bool is_smart_pointer<std::shared_ptr<T>> = true;
template<typename T>
constexpr bool is_smart_pointer<std::weak_ptr<T>> = true;
template<typename T>
constexpr bool is_smart_pointer<std::unique_ptr<T>> = true;

template<typename T>
constexpr bool is_pointer_type = is_pointer<T> || is_smart_pointer<T>;

using std::pointer_traits;
} // namespace aw
#endif//aw_traits_is_smart_pointer_h
