/*
 * Copyright (C) 2016  Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_meta_index_of_h
#define aw_meta_index_of_h
#include <type_traits>
#include <aw/meta/find_index.h>
namespace aw {
template<typename T, typename...Ts>
constexpr size_t index_of = find_index<std::is_same<_1,T>, Ts...>;
} // namespace aw
#endif//aw_meta_index_of_h
