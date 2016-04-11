/*
 * Copyright (C) 2016  Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_traits_basic_traits
#define aw_traits_basic_traits
#include <string>
#include <utility>
#include <type_traits>
#include <aw/types/traits/void_t.h>
namespace aw {
namespace detail {

template<typename T>
struct IsInt : std::integral_constant<
	bool,
	std::is_integral<T>::value
> { };
template<>
struct IsInt<bool> : std::false_type { };

template<typename T>
struct IsFloat : std::integral_constant<
	bool,
	std::is_floating_point<T>::value
> { };


template<typename>
struct IsString : std::false_type{ };
template<class CharT, class Traits, class Alloc>
struct IsString<std::basic_string<CharT, Traits, Alloc>> : std::true_type{ };

template<typename T>
struct IsBool  :  std::is_same<T, bool>{};
} // namespace detail

/* Basic type classes (yes, std::string is considered “basic”) */
template<typename T>
constexpr auto is_int       = detail::IsInt<T>::value;
template<typename T>
constexpr auto is_float     = detail::IsFloat<T>::value;
template<typename T>
constexpr auto is_string    = detail::IsString<T>::value;
template<typename T>
constexpr auto is_bool      = detail::IsBool<T>::value;
template<typename T>
constexpr auto is_pointer   = std::is_pointer<T>::value;

template<typename T>
constexpr auto is_arithmetic = std::is_arithmetic<T>::value;

template<typename T>
constexpr auto is_polymorphic = std::is_polymorphic<T>::value;

template<typename T>
constexpr auto is_trivially_copyable = std::is_trivially_copyable<T>::value;
} // namespace aw
#endif//aw_traits_basic_traits
