/*
 * Copyright (C) 2016  Hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_graphics_glsl_types_h
#define aw_graphics_glsl_types_h
#include <aw/math/matrix.h>
#include <array>
namespace aw {
namespace gl3 {
template<size_t N, size_t M, typename T>
using mat = math::matrix<T,M,N>;

using mat4 = mat<4,4,float>;
using mat3 = mat<3,3,float>;

template<typename T, size_t N, size_t M>
auto array(mat<N,M,T> m)
{
	// TODO: better?
	std::array<T,N*M> arr{};
	transpose(m);
	size_t idx = 0;
	m.for_each([&] (T const& ele) {
		arr[idx++] = ele;
	});
	return arr;
}
} // namespace gl3
} // namespace aw
#endif//aw_graphics_glsl_vec_h
