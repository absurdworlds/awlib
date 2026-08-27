/*
 * Copyright (C) 2016  Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_meta_always_false_h
#define aw_meta_always_false_h
namespace aw {
template<typename...>
constexpr bool always_false = false;
} // namespace aw
#endif//aw_meta_always_false_h
