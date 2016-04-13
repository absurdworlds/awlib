/*
 * Copyright (C) 2016  Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_types_mem_fn_h
#define aw_types_mem_fn_h
namespace aw {
namespace _impl {
template<class signature>
struct mem_fn;

template<class T, typename R, typename...Args>
struct mem_fn<R(T*, Args...)> {
	using type = R (T::*)(Args...);
};
} // namespace _impl

/*!
 * Convenience typedef.
 *
 * Converts function pointer with signature
 * R(   *)(T*, Args...)
 * into member function pointer
 * R(T::*)(    Args...)
 */
template<class signature>
using mem_fn = typename _impl::mem_fn<signature>::type;

/*!
 * Undefined class for use as placeholder in mem_fn.
 * \example
 *    mem_fn<void(aw::_unknown*, Args...)>
 */
class _unknown;
} // namespace aw
#endif//aw_types_mem_fn_h
