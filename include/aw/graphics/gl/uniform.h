/*
 * Copyright (C) 2016  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_graphics_gl3_uniform_h
#define aw_graphics_gl3_uniform_h
#include <aw/graphics/gl/types.h>
#include <aw/graphics/gl/glsl_types.h>
namespace aw {
namespace gl3 {
enum class uniform_location : GLint {};

constexpr uniform_location invalid_uniform{ uniform_location(-1) };

struct uniform_proxy {
	uniform_proxy() = delete;
	uniform_proxy(uniform_proxy const&) = delete;

	template<typename T>
	void operator=(T v) { set(v); }
	template<typename T>
	void operator=(vec<2,T> v) { set(v[0], v[1]); }
	template<typename T>
	void operator=(vec<3,T> v) { set(v[0], v[1], v[2]); }
	template<typename T>
	void operator=(vec<4,T> v) { set(v[0], v[1], v[2], v[3]); }

	// TODO: all types
	void set(GLfloat x);
	void set(GLfloat x, GLfloat y);
	void set(GLfloat x, GLfloat y, GLfloat z);
	void set(GLfloat x, GLfloat y, GLfloat z, GLfloat w);

private:
	friend struct program;
	uniform_proxy(uniform_location location)
		: location{location}
	{}

	uniform_location location = invalid_uniform;
};

} // namespace gl3
} // namespace aw
#endif//aw_graphics_gl3_uniform_h
