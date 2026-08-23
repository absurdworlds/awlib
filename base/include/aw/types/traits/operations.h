/*
 * Copyright (C) 2016  Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_traits_operations_h
#define aw_traits_operations_h
#include <type_traits>
#include <aw/meta/void_t.h>
namespace aw {
using std::declval;

namespace ops {

template<typename T>
using subscript = decltype( declval<T>()[ 0 ] );

} // namespace ops
} // namespace aw
#endif//aw_traits_is_iterable_h
