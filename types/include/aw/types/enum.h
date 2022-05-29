/*
 * Copyright (C) 2017  Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_types_enum_h
#define aw_types_enum_h
#include <type_traits>
namespace aw {
template<typename Enum>
using underlying_type = typename std::underlying_type<Enum>::type;

/*! Convert enum to value of its underlying type */
template<typename Enum>
constexpr auto underlying(Enum e)
{
	return static_cast<underlying_type<Enum>>(e);
}
} // namespace aw
#endif//aw_types_enum_h
