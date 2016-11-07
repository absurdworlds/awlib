/*
 * Copyright (C) 2016  Hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_glsl_types_h
#define aw_glsl_types_h
#include <aw/meta/void_t.h>
#include <aw/types/support/to_array.h>
#include <aw/types/traits/operations.h>
namespace aw {
template<size_t N, typename T>
struct vec {
	std::array<T,N> v;

	constexpr vec(vec const&) = default;
	template<typename V, typename = void_t<ops::subscript<V>> >
	constexpr vec(V&& v) : v{ array::make<N>(std::forward<V>(v)) } {}
	template<typename... U>
	constexpr vec(U...u) : v{T(u)...} {}
	constexpr T operator[](size_t n) { return v[n]; }
};

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

} // namespace aw
#endif//aw_glsl_types_h
