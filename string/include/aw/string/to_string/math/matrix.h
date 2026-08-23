/*
 * Copyright (C) 2016  absurdworlds
 * Copyright (C) 2016  Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_math_matrix_to_string_h
#define aw_math_matrix_to_string_h
#include <aw/math/matrix.h>
#include <aw/utility/to_string/math/vector.h>
namespace aw {
namespace math {
/*!
 * Convert math::matrix to string
 * \return
 *    String in format
 *    "{{mat.get(0,0), ..., mat.get(0,N)}, ..., {mat.get(M,0), ..., mat.get(M,N)}}"
 */
template<typename T, size_t M, size_t N, typename Formatter = formatter::pretty_print>
std::string to_string(matrix<T,M,N> const& mat, Formatter&& fmt = Formatter{})
{
	fmt.compound_start();
	for (size_t i = 0; i < M; ++i)
		fmt.value( mat.row(i) );
	fmt.compound_end();
	return fmt;
}
} // namespace math
} // namespace aw
#endif//aw_math_matrix_to_string_h
