/*
 * Copyright (C) 2022  absurdworlds
 * Copyright (C) 2022  hedede <haddayn@gmail.com>
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
namespace enum_bit_operators {
template<typename Enum>
	requires( std::is_enum_v<Enum> )
Enum operator&(Enum a, Enum b)
{
	using underlying = std::underlying_type_t<Enum>;
	return Enum( underlying(a) & underlying(b) );
}

template<typename Enum>
	requires( std::is_enum_v<Enum> )
Enum& operator&=(Enum& a, Enum b)
{
	return a = (a & b);
}

template<typename Enum>
	requires( std::is_enum_v<Enum> )
Enum operator|(Enum a, Enum b)
{
	using underlying = std::underlying_type_t<Enum>;
	return Enum( underlying(a) & underlying(b) );
}

template<typename Enum>
	requires( std::is_enum_v<Enum> )
Enum& operator|=(Enum& a, Enum b)
{
	return a = (a | b);
}

template<typename Enum>
	requires( std::is_enum_v<Enum> )
Enum operator^(Enum a, Enum b)
{
	using underlying = std::underlying_type_t<Enum>;
	return Enum( underlying(a) & underlying(b) );
}

template<typename Enum>
	requires( std::is_enum_v<Enum> )
Enum& operator^=(Enum& a, Enum b)
{
	return a = (a ^ b);
}
} // namespace enum_bit_operators
} // namespace aw

#endif//aw_types_enum_h
