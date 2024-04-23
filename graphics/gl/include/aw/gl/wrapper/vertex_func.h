/*
 * Copyright (C) 2016  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_graphics_awgl_vertex_func_h
#define aw_graphics_awgl_vertex_func_h
#include <aw/gl/api/gl_33.h>
#include <aw/types/enum.h>

namespace aw::gl {
//------------------------------------------------------------------------------
inline void gen_vertex_arrays(GLsizei n, GLuint * arrays)
{
	::gl::gen_vertex_arrays(n, arrays);
}
inline void bind_vertex_array(GLuint array)
{
	::gl::bind_vertex_array(array);
}
inline void delete_vertex_arrays(GLsizei n, const GLuint * arrays)
{
	::gl::delete_vertex_arrays(n, arrays);
}
inline GLboolean is_vertex_array(GLuint ren_array)
{
	return ::gl::is_vertex_array(ren_array);
}
//------------------------------------------------------------------------------
inline void bind_attrib_location(GLuint program, GLuint index, const GLchar * name)
{
	::gl::bind_attrib_location(program, index, name);
}

inline void enable_vertex_attrib_array(GLuint index)
{
	::gl::enable_vertex_attrib_array(index);
}
inline void disable_vertex_attrib_array(GLuint index)
{
	::gl::disable_vertex_attrib_array(index);
}
//------------------------------------------------------------------------------
inline void get_vertex_attrib_pointer(GLuint index, GLenum pname, void ** pointer)
{
	::gl::get_vertex_attrib_pointer_v(index, pname, pointer);
}
inline void get_vertex_attrib(GLuint index, GLenum pname, GLdouble * params)
{
	::gl::get_vertex_attrib_dv(index, pname, params);
}
inline void get_vertex_attrib(GLuint index, GLenum pname, GLfloat * params)
{
	::gl::get_vertex_attrib_fv(index, pname, params);
}
inline void get_vertex_attrib(GLuint index, GLenum pname, GLint * params)
{
	::gl::get_vertex_attrib_iv(index, pname, params);
}
inline void get_vertex_attrib_i(GLuint index, GLenum pname, GLint * params)
{
	::gl::get_vertex_attrib_i_iv(index, pname, params);
}
inline void get_vertex_attrib_i(GLuint index, GLenum pname, GLuint * params)
{
	::gl::get_vertex_attrib_i_uiv(index, pname, params);
}
//------------------------------------------------------------------------------
inline void vertex_attrib_1d(GLuint index, GLdouble x)
{
	::gl::vertex_attrib_1d(index, x);
}
inline void vertex_attrib_1dv(GLuint index, const GLdouble * v)
{
	::gl::vertex_attrib_1dv(index, v);
}
inline void vertex_attrib_1f(GLuint index, GLfloat x)
{
	::gl::vertex_attrib_1f(index, x);
}
inline void vertex_attrib_1fv(GLuint index, const GLfloat * v)
{
	::gl::vertex_attrib_1fv(index, v);
}
inline void vertex_attrib_1s(GLuint index, GLshort x)
{
	::gl::vertex_attrib_1s(index, x);
}
inline void vertex_attrib_1sv(GLuint index, const GLshort * v)
{
	::gl::vertex_attrib_1sv(index, v);
}
inline void vertex_attrib_2d(GLuint index, GLdouble x, GLdouble y)
{
	::gl::vertex_attrib_2d(index, x, y);
}
inline void vertex_attrib_2dv(GLuint index, const GLdouble * v)
{
	::gl::vertex_attrib_2dv(index, v);
}
inline void vertex_attrib_2f(GLuint index, GLfloat x, GLfloat y)
{
	::gl::vertex_attrib_2f(index, x, y);
}
inline void vertex_attrib_2fv(GLuint index, const GLfloat * v)
{
	::gl::vertex_attrib_2fv(index, v);
}
inline void vertex_attrib_2s(GLuint index, GLshort x, GLshort y)
{
	::gl::vertex_attrib_2s(index, x, y);
}
inline void vertex_attrib_2sv(GLuint index, const GLshort * v)
{
	::gl::vertex_attrib_2sv(index, v);
}
inline void vertex_attrib_3d(GLuint index, GLdouble x, GLdouble y, GLdouble z)
{
	::gl::vertex_attrib_3d(index, x, y, z);
}
inline void vertex_attrib_3dv(GLuint index, const GLdouble * v)
{
	::gl::vertex_attrib_3dv(index, v);
}
inline void vertex_attrib_3f(GLuint index, GLfloat x, GLfloat y, GLfloat z)
{
	::gl::vertex_attrib_3f(index, x, y, z);
}
inline void vertex_attrib_3fv(GLuint index, const GLfloat * v)
{
	::gl::vertex_attrib_3fv(index, v);
}
inline void vertex_attrib_3s(GLuint index, GLshort x, GLshort y, GLshort z)
{
	::gl::vertex_attrib_3s(index, x, y, z);
}
inline void vertex_attrib_3sv(GLuint index, const GLshort * v)
{
	::gl::vertex_attrib_3sv(index, v);
}
inline void vertex_attrib_4nbv(GLuint index, const GLbyte * v)
{
	::gl::vertex_attrib_4nbv(index, v);
}
inline void vertex_attrib_4niv(GLuint index, const GLint * v)
{
	::gl::vertex_attrib_4niv(index, v);
}
inline void vertex_attrib_4nsv(GLuint index, const GLshort * v)
{
	::gl::vertex_attrib_4nsv(index, v);
}
inline void vertex_attrib_4nub(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w)
{
	::gl::vertex_attrib_4nub(index, x, y, z, w);
}
inline void vertex_attrib_4nubv(GLuint index, const GLubyte * v)
{
	::gl::vertex_attrib_4nubv(index, v);
}
inline void vertex_attrib_4nuiv(GLuint index, const GLuint * v)
{
	::gl::vertex_attrib_4nuiv(index, v);
}
inline void vertex_attrib_4nusv(GLuint index, const GLushort * v)
{
	::gl::vertex_attrib_4nusv(index, v);
}
inline void vertex_attrib_4bv(GLuint index, const GLbyte * v)
{
	::gl::vertex_attrib_4bv(index, v);
}
inline void vertex_attrib_4d(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w)
{
	::gl::vertex_attrib_4d(index, x, y, z, w);
}
inline void vertex_attrib_4dv(GLuint index, const GLdouble * v)
{
	::gl::vertex_attrib_4dv(index, v);
}
inline void vertex_attrib_4f(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	::gl::vertex_attrib_4f(index, x, y, z, w);
}
inline void vertex_attrib_4fv(GLuint index, const GLfloat * v)
{
	::gl::vertex_attrib_4fv(index, v);
}
inline void vertex_attrib_4iv(GLuint index, const GLint * v)
{
	::gl::vertex_attrib_4iv(index, v);
}
inline void vertex_attrib_4s(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w)
{
	::gl::vertex_attrib_4s(index, x, y, z, w);
}
inline void vertex_attrib_4sv(GLuint index, const GLshort * v)
{
	::gl::vertex_attrib_4sv(index, v);
}
inline void vertex_attrib_4ubv(GLuint index, const GLubyte * v)
{
	::gl::vertex_attrib_4ubv(index, v);
}
inline void vertex_attrib_4uiv(GLuint index, const GLuint * v)
{
	::gl::vertex_attrib_4uiv(index, v);
}
inline void vertex_attrib_4usv(GLuint index, const GLushort * v)
{
	::gl::vertex_attrib_4usv(index, v);
}
inline void vertex_attrib_pointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, uintptr_t pointer)
{
	::gl::vertex_attrib_pointer(index, size, type, normalized, stride, (const void*)pointer);
}

//------------------------------------------------------------------------------
inline void vertex_attrib_i_1i(GLuint index, GLint x)
{
	::gl::vertex_attrib_i_1i(index, x);
}
inline void vertex_attrib_i_1iv(GLuint index, const GLint * v)
{
	::gl::vertex_attrib_i_1iv(index, v);
}
inline void vertex_attrib_i_1ui(GLuint index, GLuint x)
{
	::gl::vertex_attrib_i_1ui(index, x);
}
inline void vertex_attrib_i_1uiv(GLuint index, const GLuint * v)
{
	::gl::vertex_attrib_i_1uiv(index, v);
}
inline void vertex_attrib_i_2i(GLuint index, GLint x, GLint y)
{
	::gl::vertex_attrib_i_2i(index, x, y);
}
inline void vertex_attrib_i_2iv(GLuint index, const GLint * v)
{
	::gl::vertex_attrib_i_2iv(index, v);
}
inline void vertex_attrib_i_2ui(GLuint index, GLuint x, GLuint y)
{
	::gl::vertex_attrib_i_2ui(index, x, y);
}
inline void vertex_attrib_i_2uiv(GLuint index, const GLuint * v)
{
	::gl::vertex_attrib_i_2uiv(index, v);
}
inline void vertex_attrib_i_3i(GLuint index, GLint x, GLint y, GLint z)
{
	::gl::vertex_attrib_i_3i(index, x, y, z);
}
inline void vertex_attrib_i_3iv(GLuint index, const GLint * v)
{
	::gl::vertex_attrib_i_3iv(index, v);
}
inline void vertex_attrib_i_3ui(GLuint index, GLuint x, GLuint y, GLuint z)
{
	::gl::vertex_attrib_i_3ui(index, x, y, z);
}
inline void vertex_attrib_i_3uiv(GLuint index, const GLuint * v)
{
	::gl::vertex_attrib_i_3uiv(index, v);
}
inline void vertex_attrib_i_4bv(GLuint index, const GLbyte * v)
{
	::gl::vertex_attrib_i_4bv(index, v);
}
inline void vertex_attrib_i_4i(GLuint index, GLint x, GLint y, GLint z, GLint w)
{
	::gl::vertex_attrib_i_4i(index, x, y, z, w);
}
inline void vertex_attrib_i_4iv(GLuint index, const GLint * v)
{
	::gl::vertex_attrib_i_4iv(index, v);
}
inline void vertex_attrib_i_4sv(GLuint index, const GLshort * v)
{
	::gl::vertex_attrib_i_4sv(index, v);
}
inline void vertex_attrib_i_4ubv(GLuint index, const GLubyte * v)
{
	::gl::vertex_attrib_i_4ubv(index, v);
}
inline void vertex_attrib_i_4ui(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w)
{
	::gl::vertex_attrib_i_4ui(index, x, y, z, w);
}
inline void vertex_attrib_i_4uiv(GLuint index, const GLuint * v)
{
	::gl::vertex_attrib_i_4uiv(index, v);
}
inline void vertex_attrib_i_4usv(GLuint index, const GLushort * v)
{
	::gl::vertex_attrib_i_4usv(index, v);
}
inline void vertex_attrib_i_pointer(GLuint index, GLint size, GLenum type, GLsizei stride, const void * pointer)
{
	::gl::vertex_attrib_i_pointer(index, size, type, stride, pointer);
}

//------------------------------------------------------------------------------
inline void vertex_attrib_divisor(GLuint index, GLuint divisor)
{
	::gl::vertex_attrib_divisor(index, divisor);
}
inline void vertex_attrib_p_1ui(GLuint index, GLenum type, GLboolean normalized, GLuint value)
{
	::gl::vertex_attrib_p_1ui(index, type, normalized, value);
}
inline void vertex_attrib_p_1uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint * value)
{
	::gl::vertex_attrib_p_1uiv(index, type, normalized, value);
}
inline void vertex_attrib_p_2ui(GLuint index, GLenum type, GLboolean normalized, GLuint value)
{
	::gl::vertex_attrib_p_2ui(index, type, normalized, value);
}
inline void vertex_attrib_p_2uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint * value)
{
	::gl::vertex_attrib_p_2uiv(index, type, normalized, value);
}
inline void vertex_attrib_p_3ui(GLuint index, GLenum type, GLboolean normalized, GLuint value)
{
	::gl::vertex_attrib_p_3ui(index, type, normalized, value);
}
inline void vertex_attrib_p_3uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint * value)
{
	::gl::vertex_attrib_p_3uiv(index, type, normalized, value);
}
inline void vertex_attrib_p_4ui(GLuint index, GLenum type, GLboolean normalized, GLuint value)
{
	::gl::vertex_attrib_p_4ui(index, type, normalized, value);
}
inline void vertex_attrib_p_4uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint * value)
{
	::gl::vertex_attrib_p_4uiv(index, type, normalized, value);
}
} // namespace aw::gl

#endif//aw_graphics_awgl_vertex_func_h
