/*
 * Copyright (C) 2018  hedede <haddayn@gmail.com>
 * Copyright (C) 2018  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_math_transform_h
#define aw_math_transform_h
#include <aw/math/matrix.h>
namespace aw::math {
template<typename T, size_t N>
matrix<T,N+1,N+1> translation_matrix(vector<T,N> const& vec)
{
	auto mat = identity_matrix<T,N+1>;
	// initialize last column of the matrix with vector v
	// TODO: matrix::set_col(i, vec);
	// TODO: append(vector<N>, x) -> vector<N+1>
	for (auto i = 0; i < N; ++i)
		mat.get(i, N) = vec[i];
	return mat;
}

template<typename T, size_t N>
matrix<T,N+1,N+1> make_transform(vector<T,N> const& vec, matrix<T,N,N> const& rot)
{
	auto mat = translation_matrix(vec);
	mat = rot;
	return mat;
}
} // namespace aw::math
#endif//aw_math_transform_h
