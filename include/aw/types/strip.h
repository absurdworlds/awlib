/*
 * Copyright (C) 2016  Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_traits_strip
#define aw_traits_strip
#include <utility>
#include <aw/meta/conditional.h>
namespace aw {
template<typename T>
using remove_cv = std::remove_cv_t<T>;

template<typename T>
using remove_const = std::remove_const_t<T>;

template<typename T>
using remove_pointer = std::remove_pointer_t<T>;

template<typename T>
using remove_pointer_cv = std::remove_pointer_t<std::remove_cv_t<T>>;

template<typename T>
using remove_pointer_const = std::remove_pointer_t<std::remove_const_t<T>>;

template<typename T>
using remove_reference = std::remove_reference_t<T>;

template<typename T>
using remove_reference_cv = std::remove_reference_t<std::remove_cv_t<T>>;

template<typename T>
using remove_reference_const = std::remove_reference_t<std::remove_const_t<T>>;

namespace _impl {
template <typename T> struct strip_pointers { using type = T; };
template <typename T> struct strip_pointers<T*> {
	using type = typename strip_pointers<T>::type;
};
template <typename T> struct strip_pointers<T const*> {
	using type = typename strip_pointers<T>::type;
};
template <typename T> struct strip_pointers<T volatile*> {
	using type = typename strip_pointers<T>::type;
};
} // namespace _impl

template <typename T>
using strip_pointers = typename _impl::strip_pointers<T>::type;

/*! Copies constness of type A to type B*/
template<typename A, typename B>
using copy_const = conditional<is_const<A>, B const, remove_const<B>>;
} // namespace aw
#endif//aw_traits_strip
