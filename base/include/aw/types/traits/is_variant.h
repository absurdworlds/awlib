/*
 * Copyright (C) 2026 Hedede <mail@hedede.me>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_traits_is_variant_h
#define aw_traits_is_variant_h
#include <utility>
#include <variant>
namespace aw {
template<typename T>
struct is_std_variant : std::false_type {};
template<typename... Ts>
struct is_std_variant<std::variant<Ts...>> : std::true_type {};

template<typename T>
constexpr bool is_std_variant_v = is_std_variant<T>::value;
} // namespace aw
#endif//aw_traits_is_variant_h
