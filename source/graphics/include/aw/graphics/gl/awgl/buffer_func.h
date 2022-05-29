/*
 * Copyright (C) 2016  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_graphics_awgl_buffer_func_h
#define aw_graphics_awgl_buffer_func_h
#include <aw/graphics/gl/api/gl_33.h>
#include <aw/types/enum.h>
namespace aw {
namespace gl {
//------------------------------------------------------------------------------
inline void gen_buffers(GLsizei n, GLuint * buffers)
{
	::gl::gen_buffers(n, buffers);
}
inline void delete_buffers(GLsizei n, const GLuint * buffers)
{
	::gl::delete_buffers(n, buffers);
}
inline GLboolean is_buffer(GLuint buffer)
{
	return ::gl::is_buffer(buffer);
}

//------------------------------------------------------------------------------
inline void bind_buffer(GLenum target, GLuint buffer)
{
	::gl::bind_buffer(target, buffer);
}
inline void bind_buffer_base(GLenum target, GLuint index, GLuint buffer)
{
	::gl::bind_buffer_base(target, index, buffer);
}
inline void bind_buffer_range(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size)
{
	::gl::bind_buffer_range(target, index, buffer, offset, size);
}
//------------------------------------------------------------------------------
inline void * map_buffer(GLenum target, GLenum access)
{
	return ::gl::map_buffer(target, access);
}
inline GLboolean unmap_buffer(GLenum target)
{
	return ::gl::unmap_buffer(target);
}

//------------------------------------------------------------------------------
inline void buffer_data(GLenum target, GLsizeiptr size, const void * data, GLenum usage)
{
	::gl::buffer_data(target, size, data, usage);
}
inline void buffer_sub_data(GLenum target, GLintptr offset, GLsizeiptr size, const void * data)
{
	::gl::buffer_sub_data(target, offset, size, data);
}
//------------------------------------------------------------------------------
inline void get_buffer_parameter(GLenum target, GLenum pname, GLint * params)
{
	::gl::get_buffer_parameter_iv(target, pname, params);
}
inline void get_buffer_pointer(GLenum target, GLenum pname, void ** params)
{
	::gl::get_buffer_pointer_v(target, pname, params);
}
inline void get_buffer_sub_data(GLenum target, GLintptr offset, GLsizeiptr size, void * data)
{
	::gl::get_buffer_sub_data(target, offset, size, data);
}

} // namespace gl
} // namespace aw
#endif//aw_graphics_awgl_buffer_func_h
