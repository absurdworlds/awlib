/*
 * Copyright (C) 2016  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_internal_gl3_shader_h
#define aw_internal_gl3_shader_h
#include <aw/graphics/gl/shader.h>
namespace aw {
namespace gl3 {
/* Kinda hackish thing to keep external code from
 * manipulating shader handles, without adding bunch of friends */

struct shader;

struct shader_handle {
	GLuint handle;
	operator GLuint() { return handle; }
};

shader::operator shader_handle()
{
	return {_shader};
}

namespace {
GLuint handle(shader& shd)  { return shader_handle(shd); }
}

} // namespace gl3
} // namespace aw
#endif//aw_internal_gl3_handles_h
