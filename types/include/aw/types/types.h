/*
 * Copyright (C) 2014-2016 absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_types_h
#define aw_types_h
#include <cstddef>
#include <cstdint>
namespace aw {
//!@{
//! Shorthands for integer types
using u8  = std::uint8_t;
using i8  = std::int8_t;

using u16 = std::uint16_t;
using i16 = std::int16_t;

using u32 = std::uint32_t;
using i32 = std::int32_t;

using u64 = std::uint64_t;
using i64 = std::int64_t;

using size_t    = std::size_t;
using ptrdiff_t = std::ptrdiff_t;
using intptr_t  = std::intptr_t;
using uintptr_t = std::uintptr_t;
//!@}

//!@{
//! Shorthands for floating point types
using f32 = float;
using f64 = double;
//!@}

using std::nullptr_t;
using std::byte;
} // namespace aw
#endif //aw_types_h
