/*
 * Copyright (C) 2016  absurdworlds
 * Copyright (C) 2016  Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_math_vector_to_string_h
#define aw_math_vector_to_string_h
#include <aw/utility/to_string/to_string.h>
#include <aw/math/vector.h>
namespace aw {
/*!
 * Convert math::vector to string
 * \return
 *    String in format "{vec[0], vec[1], ..., vec[N]}"
 */
// TODO: why ADL doesn't find it?
//template<typename T, size_t N>
struct string_converter<math::vector<T,N>> {
	std::string operator()( math::vector<T,N> const& vec ) const
	{
		std::string str = to_string( get<0>(vec) );
		for (size_t i = 1; i < N; ++i) {
			str.append(", ");
			str.append( to_string(vec[i]) );
		}
		return str;
	}
};
} // namespace aw
#endif//aw_math_vector_to_string_h
