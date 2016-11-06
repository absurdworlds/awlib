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
#if __has_include(<optional>)
#include <optional>
namespace aw {
using std::optional;
using std::nullopt_t;
using std::nullopt;
} // namespace aw
#elif __has_include(<experimental/optional>)
#include <experimental/optional>
namespace aw {
using std::experimental::optional;
using std::experimental::nullopt_t;
using std::experimental::nullopt;
} // namespace aw
#endif
#endif //aw_types_optional_h
