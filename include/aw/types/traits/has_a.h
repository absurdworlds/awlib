/*
 * Copyright (C) 2016  Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_traits_has_a
#define aw_traits_has_a
#include <utility>
#include <type_traits>
namespace aw {
using yes = std::true_type;
using no = std::false_type;

#define AW_DECLARE_HAS_NON_MEMBER(func) \
namespace detail { \
template<class... Args> \
struct has_non_member_##func { \
	template<class... Ty> \
	static auto check(int) -> decltype( func(std::declval<Ty&>()...), yes() ); \
\
	template<class... Ty> \
	static auto check(...) -> no; \
\
	static const bool value = std::is_same<decltype( check<Args...>(0) ), yes>::value;\
}; \
} \
template<class... Args> \
constexpr bool has_non_member_##func = detail::has_non_member_##func<Args...>::value

#define AW_DECLARE_HAS_MEMBER(func) \
namespace detail { \
template<class C, class... Args> \
struct has_member_##func { \
	template<class T, class... Ty> \
	static auto check(int) -> decltype( std::declval<T&>().func(std::declval<Ty&>()...), yes() ); \
\
	template<class T, class... Ty> \
	static auto check(...) -> no; \
\
	static const bool value = std::is_same<decltype( check<C, Args...>(0) ), yes>::value;\
}; \
} \
template<class C, class... Args> \
constexpr bool has_member_##func = detail::has_member_##func<C, Args...>::value

#define AW_DECLARE_HAS_MEMBER_VAR(var) \
namespace detail { \
template<class C, class = void> \
struct has_var_##var : std::false_type {}; \
template<class C> \
struct has_var_##var<C, decltype(std::declval<C>().var, void())> : std::true_type {}; \
} \
template<class C> \
constexpr bool has_member_##var = detail::has_var_##var<C>::value

#define AW_DECLARE_HAS_STATIC_VAR(var) \
namespace detail { \
template<class C, class = void> \
struct has_static_##var : std::false_type {}; \
template<class C> \
struct has_static_##var<C, decltype(C::var, void())> : std::true_type {}; \
} \
template<class C> \
constexpr bool has_static_##var = detail::has_static_##var<C>::value
} // namespace aw
#endif//aw_traits_has_a
