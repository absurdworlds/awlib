/*
 * Copyright (C) 2016  Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_traits_detection
#define aw_traits_detection
//#include <experimental/type_traits>
#include <aw/meta/void_t.h>
namespace aw {
namespace _impl {
template <class, template<class...> class Op, class... Args>
struct detector : std::false_type {};

template <template<class...> class Op, class... Args>
struct detector<void_t<Op<Args...>>, Op, Args...> : std::true_type {};
} // namespace _impl

template <template<class...> class Op, class... Args>
constexpr bool is_detected = aw::_impl::detector<void, Op, Args...>::value;
} // namespace aw
#endif//aw_traits_detection
