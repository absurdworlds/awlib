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
#include <aw/graphics/gl/shader.h>
#include <vector>
namespace aw {
namespace gl3 {
/*!
 * Helper for setting uniforms, stores location of an uniform
 * in the program it was obtained from.
 * This class can be stored somewhere to change uniform values
 * without having to look it up again, but beware that it does
 * *not* check if correct program is currently active (or if
 * any program is active).
 */
struct uniform_value {
	uniform_value() = default;
	uniform_value(uniform_value const&) = default;

	bool is_valid() const { return location >= 0; }

	// TODO: all types
	void set(GLfloat x);
	void set(GLfloat x, GLfloat y);
	void set(GLfloat x, GLfloat y, GLfloat z);
	void set(GLfloat x, GLfloat y, GLfloat z, GLfloat w);

private:
	friend struct program;
	uniform_value(GLint location)
		: location{location}
	{}

	GLint location = -1;
};

} // namespace gl3
} // namespace aw
#endif//aw_graphics_gl3_uniform_h
