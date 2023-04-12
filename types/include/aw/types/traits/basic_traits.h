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
#include <aw/meta/void_t.h>
#include <aw/types/string_view.h>
#include <string>
#include <type_traits>
#include <utility>
namespace aw {
using std::declval;

template<typename T>
constexpr auto is_arithmetic = std::is_arithmetic<T>::value;
template<typename T>
constexpr auto is_signed = std::is_signed<T>::value;
template<typename T>
constexpr auto is_unsigned = std::is_unsigned<T>::value;

template<typename T>
constexpr bool is_reference = std::is_reference<T>::value;
template<typename T>
constexpr bool is_lvalue_reference = std::is_lvalue_reference<T>::value;
template<typename T>
constexpr bool is_rvalue_reference = std::is_rvalue_reference<T>::value;

template<typename T>
constexpr auto is_class       = std::is_class<T>::value;
template<typename T>
constexpr auto is_polymorphic = std::is_polymorphic<T>::value;
template<typename T>
constexpr auto is_abstract    = std::is_abstract<T>::value;
template<typename T>
constexpr auto is_pod         = std::is_trivial<T>::value && std::is_standard_layout<T>::value;


template<typename T>
constexpr auto is_trivially_copyable = std::is_trivially_copyable<T>::value;

template<typename T, typename...Args>
constexpr auto is_constructible = std::is_constructible<T, Args...>::value;

template<typename A, typename B>
constexpr bool is_convertible = std::is_convertible<A, B>::value;

template<typename Fn, typename...Args>
constexpr bool is_invocable = std::is_invocable<Fn, Args...>::value;

template<class Base, class Derived>
constexpr auto is_base_of = std::is_base_of<Base,Derived>::value;

template<class A, class B>
constexpr auto is_same [[deprecated("Use is_same_v")]] = std::is_same<A,B>::value;

template<class A, class B>
constexpr auto is_same_v = std::is_same<A,B>::value;

template<typename T>
constexpr bool is_const = std::is_const<T>::value;
namespace detail {
template <typename Call> struct result_of {};

template <typename Call, typename... Args>
struct result_of<Call(Args...)> : std::invoke_result<Call, Args...> {};
} // namespace detail

template <typename Call>
using result_of [[deprecated]] = detail::result_of<Call>;

template<typename T>
struct is_floating_point_t : std::is_floating_point<T> { };
template<typename T>
constexpr bool is_floating_point = is_floating_point_t<T>::value;

template<typename T>
using is_float_t = is_floating_point_t<T>;

template<typename T>
struct is_int_t : std::is_integral<T> { };
/*!
 * Specialization for bool — most of the time I want
 * special treatment for boolean type
 */
template<> struct is_int_t<bool> : std::false_type { };


template<typename>
struct is_string_t : std::false_type{ };
template<class CharT, class Traits, class Alloc>
struct is_string_t<std::basic_string<CharT, Traits, Alloc>> : std::true_type{ };
template<class CharT, class Traits>
struct is_string_t<basic_string_view<CharT, Traits>> : std::true_type{ };

/* Basic type categories (yes, std::string is considered “basic”) */
template<typename T>
constexpr bool is_int       = is_int_t<T>::value;
template<typename T>
constexpr bool is_float     = is_floating_point<T>;
template<typename T>
constexpr bool is_string    = is_string_t<T>::value;
template<typename T>
constexpr bool is_bool      = std::is_same<T, bool>::value;
template<typename T>
constexpr bool is_pointer   = std::is_pointer<T>::value;
} // namespace aw
#endif//aw_traits_basic_traits
