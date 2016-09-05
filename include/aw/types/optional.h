/*
 * Copyright (C) 2014-2016 absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_types_optional_h
#define aw_types_optional_h
#include <experimental/optional>
namespace aw {
//!@{
//! Shorthand for std::experimental::optional
template <typename T>
using optional = std::experimental::optional<T>;

using std::experimental::nullopt_t;
//using std::experimental::nullopt;
using std::experimental::nullopt;
//!@}
} // namespace aw
#endif //aw_types_optional_h
