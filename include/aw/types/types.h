/*
 * Copyright (C) 2014-2016 absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_types_
#define aw_types_
#include <cstddef>
#include <cstdint>
#include <memory>
#include <experimental/optional>
namespace aw {
// Shorthands for integer types
using u8  = std::uint8_t;
using i8  = std::int8_t;

using u16 = std::uint16_t;
using i16 = std::int16_t;

using u32 = std::uint32_t;
using i32 = std::int32_t;

using u64 = std::uint64_t;
using i64 = std::int64_t;

using size_t = std::size_t;
using diff_t = std::ptrdiff_t;

//        ... for floating point types
using f32 = float;
using f64 = double;

//! Shorthand for std::unique_ptr template
template <typename T>
using uptr = std::unique_ptr<T>;

//! Shorthand for std::experimental::optional template
template <typename T>
using opt = std::experimental::optional<T>;

using nullopt_t = std::experimental::nullopt_t;

constexpr nullopt_t nullopt = std::experimental::nullopt;
} // namespace aw
#endif //aw_types_
