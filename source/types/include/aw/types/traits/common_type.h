/*
 * Copyright (C) 2016  Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_traits_common_type_h
#define aw_traits_common_type_h
#include <type_traits>
namespace aw {
template<typename...Ts>
struct common_type_t : std::common_type<Ts...> {};
template<typename...Ts>
using common_type = typename std::common_type<Ts...>::type;
} // namespace aw
#endif//aw_traits_common_type_h
