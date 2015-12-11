/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_types_
#define _aw_types_
#include <cstddef>
#include <cstdint>
#include <memory>
#include <experimental/optional>

namespace aw {
typedef uint8_t        u8;
typedef  int8_t        i8;

typedef uint16_t       u16;
typedef  int16_t       i16;

typedef uint32_t       u32;
typedef  int32_t       i32;

typedef uint64_t       u64;
typedef  int64_t       i64;

typedef ptrdiff_t      diff_t;

typedef float          f32;
typedef double         f64;

template <typename T>
using uptr = std::unique_ptr<T>;

template <typename T>
using opt = std::experimental::optional<T>;

using nullopt_t = std::experimental::nullopt_t;

constexpr nullopt_t nullopt = std::experimental::nullopt;
} // namespace aw
#endif //_aw_types_
