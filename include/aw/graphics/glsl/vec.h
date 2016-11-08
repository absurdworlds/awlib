/*
 * Copyright (C) 2016  Hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_graphics_glsl_vec_h
#define aw_graphics_glsl_vec_h
#include <aw/math/vector.h>
namespace aw {
namespace gl3 {
template<size_t N, typename T>
using vec = math::vector<T, N>;

using vec2 = vec<2, float>;
using vec3 = vec<3, float>;
using vec4 = vec<4, float>;

using ivec2 = vec<2, int>;
using ivec3 = vec<3, int>;
using ivec4 = vec<4, int>;

using bvec2 = vec<2, bool>;
using bvec3 = vec<3, bool>;
using bvec4 = vec<4, bool>;

using uvec2 = vec<2, unsigned>;
using uvec3 = vec<3, unsigned>;
using uvec4 = vec<4, unsigned>;

using dvec2 = vec<2, double>;
using dvec3 = vec<3, double>;
using dvec4 = vec<4, double>;
} // namespace gl3
} // namespace aw
#endif//aw_graphics_glsl_vec_h
