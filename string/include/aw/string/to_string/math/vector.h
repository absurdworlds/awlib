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
#include <aw/math/vector.h>
#include <aw/utility/to_string.h>
namespace aw {
namespace math {
/*!
 * Convert math::vector to string
 * \return
 *    String in format "{vec[0], vec[1], ..., vec[N]}"
 */
template<typename T, size_t N, typename Formatter = formatter::pretty_print>
std::string to_string(vector<T,N> const& vec, Formatter&& fmt = Formatter{})
{
	fmt.compound_start();
	for (size_t i = 0; i < N; ++i)
		fmt.value( vec[i] );
	fmt.compound_end();
	return fmt;
}
} // namespace math
} // namespace aw
#endif//aw_math_vector_to_string_h
