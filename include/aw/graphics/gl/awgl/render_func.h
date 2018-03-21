/*
 * Copyright (C) 2016  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_graphics_awgl_draw_func_h
#define aw_graphics_awgl_draw_func_h
#include <aw/graphics/gl/api/types.h>
#include <aw/types/string_view.h>
namespace aw {
namespace gl {
//------------------------------------------------------------------------------
inline void line_width(GLfloat width)
{
	::gl::line_width(width);
}
inline void point_size(GLfloat size)
{
	::gl::point_size(size);
}
inline void polygon_mode(GLenum face, GLenum mode)
{
	::gl::polygon_mode(face, mode);
}
inline void cull_face(GLenum mode)
{
	::gl::cull_face(mode);
}
inline void front_face(GLenum mode)
{
	::gl::front_face(mode);
}
inline void polygon_offset(GLfloat factor, GLfloat units)
{
	::gl::polygon_offset(factor, units);
}
//------------------------------------------------------------------------------
inline void finish(void)
{
	::gl::finish();
}
inline void flush(void)
{
	::gl::flush();
}
inline void hint(GLenum target, GLenum mode)
{
	::gl::hint(target, mode);
}

//------------------------------------------------------------------------------
inline void draw_buffer(GLenum buf)
{
	::gl::draw_buffer(buf);
}
inline void draw_arrays(GLenum mode, GLint first, GLsizei count)
{
	::gl::draw_arrays(mode, first, count);
}
inline void draw_elements(GLenum mode, GLsizei count, GLenum type, const void * indices)
{
	::gl::draw_elements(mode, count, type, indices);
}
inline void draw_range_elements(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void * indices)
{
	::gl::draw_range_elements(mode, start, end, count, type, indices);
}

//------------------------------------------------------------------------------
inline void multi_draw_arrays(GLenum mode, const GLint * first, const GLsizei * count, GLsizei drawcount)
{
	::gl::multi_draw_arrays(mode, first, count, drawcount);
}
inline void multi_draw_elements(GLenum mode, const GLsizei * count, GLenum type, const void *const* indices, GLsizei drawcount)
{
	::gl::multi_draw_elements(mode, count, type, indices, drawcount);
}
//------------------------------------------------------------------------------
inline void draw_arrays_instanced(GLenum mode, GLint first, GLsizei count, GLsizei instancecount)
{
	::gl::draw_arrays_instanced(mode, first, count, instancecount);
}

inline void draw_elements_instanced(GLenum mode, GLsizei count, GLenum type, const void * indices, GLsizei instancecount)
{
	::gl::draw_elements_instanced(mode, count, type, indices, instancecount);
}

//------------------------------------------------------------------------------
inline void draw_elements_base_vertex(GLenum mode, GLsizei count, GLenum type, const void * indices, GLint basevertex)
{
	::gl::draw_elements_base_vertex(mode, count, type, indices, basevertex);
}
inline void draw_elements_instanced_base_vertex(GLenum mode, GLsizei count, GLenum type, const void * indices, GLsizei instancecount, GLint basevertex)
{
	::gl::draw_elements_instanced_base_vertex(mode, count, type, indices, instancecount, basevertex);
}
inline void draw_range_elements_base_vertex(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void * indices, GLint basevertex)
{
	::gl::draw_range_elements_base_vertex(mode, start, end, count, type, indices, basevertex);
}
} // namespace gl
} // namespace aw
#endif//aw_graphics_awgl_draw_func_h
