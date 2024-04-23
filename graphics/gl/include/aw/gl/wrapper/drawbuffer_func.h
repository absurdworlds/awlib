/*
 * Copyright (C) 2016  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_graphics_awgl_drawbuffer_func_h
#define aw_graphics_awgl_drawbuffer_func_h
#include <aw/gl/api/types.h>
#include <aw/types/string_view.h>
namespace aw {
namespace gl {
//------------------------------------------------------------------------------
inline void clear(GLbitfield mask)
{
	::gl::clear(mask);
}
inline void clear_color(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
	::gl::clear_color(red, green, blue, alpha);
}
inline void clear_depth(GLdouble depth)
{
	::gl::clear_depth(depth);
}
inline void clear_stencil(GLint s)
{
	::gl::clear_stencil(s);
}

//------------------------------------------------------------------------------
inline void draw_buffers(GLsizei n, const GLenum * bufs)
{
	::gl::draw_buffers(n, bufs);
}
inline void blend_func(GLenum sfactor, GLenum dfactor)
{
	::gl::blend_func(sfactor, dfactor);
}
inline void blend_color(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
	::gl::blend_color(red, green, blue, alpha);
}
inline void blend_equation(GLenum mode)
{
	::gl::blend_equation(mode);
}
inline void blend_func_separate(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha)
{
	::gl::blend_func_separate(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha);
}
inline void blend_equation_separate(GLenum modeRGB, GLenum modeAlpha)
{
	::gl::blend_equation_separate(modeRGB, modeAlpha);
}
inline void color_mask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)
{
	::gl::color_mask(red, green, blue, alpha);
}

inline void logic_op(GLenum opcode)
{
	::gl::logic_op(opcode);
}

//------------------------------------------------------------------------------
inline void depth_func(GLenum func)
{
	::gl::depth_func(func);
}
inline void depth_mask(GLboolean flag)
{
	::gl::depth_mask(flag);
}
inline void depth_range(GLdouble ren_near, GLdouble ren_far)
{
	::gl::depth_range(ren_near, ren_far);
}


//------------------------------------------------------------------------------
inline void stencil_func(GLenum func, GLint ref, GLuint mask)
{
	::gl::stencil_func(func, ref, mask);
}
inline void stencil_mask(GLuint mask)
{
	::gl::stencil_mask(mask);
}
inline void stencil_op(GLenum fail, GLenum zfail, GLenum zpass)
{
	::gl::stencil_op(fail, zfail, zpass);
}

inline void stencil_func_separate(GLenum face, GLenum func, GLint ref, GLuint mask)
{
	::gl::stencil_func_separate(face, func, ref, mask);
}
inline void stencil_mask_separate(GLenum face, GLuint mask)
{
	::gl::stencil_mask_separate(face, mask);
}
inline void stencil_op_separate(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass)
{
	::gl::stencil_op_separate(face, sfail, dpfail, dppass);
}

//------------------------------------------------------------------------------
inline void scissor(GLint x, GLint y, GLsizei width, GLsizei height)
{
	::gl::scissor(x, y, width, height);
}
inline void viewport(GLint x, GLint y, GLsizei width, GLsizei height)
{
	::gl::viewport(x, y, width, height);
}
} // namespace gl
} // namespace aw
#endif//aw_graphics_awgl_drawbuffer_func_h
