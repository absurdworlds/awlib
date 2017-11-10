/*
 * Copyright (C) 2017  absurdworlds
 * Copyright (C) 2017  Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_utility_functional_forward_h
#define aw_utility_functional_forward_h
#include <utility>
namespace aw {
using std::forward;
//template<typename T> auto forward(T&& t) { return static_cast<T&&>(t); }
} // namespace aw
#endif//aw_utility_functional_forward_h
