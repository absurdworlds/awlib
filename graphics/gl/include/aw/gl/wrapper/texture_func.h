/*
 * Copyright (C) 2016  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_graphics_awgl_texture_func_h
#define aw_graphics_awgl_texture_func_h
#include <aw/gl/api/gl_33.h>
#include <aw/gl/wrapper/texture_enum.h>
#include <aw/types/enum.h>

namespace aw::gl {

//------------------------------------------------------------------------------
inline void gen_textures(GLsizei n, texture_handle* textures)
{
	::gl::gen_textures(n, (GLuint*)textures);
}

inline void delete_textures(GLsizei n, const texture_handle* textures)
{
	::gl::delete_textures(n, (const GLuint*)textures);
}

inline void bind_texture(GLenum target, texture_handle texture)
{
	::gl::bind_texture(target, underlying(texture));
}

inline GLboolean is_texture(GLuint texture)
{
	return ::gl::is_texture(texture);
}

inline GLboolean is_texture(texture_handle texture)
{
	return is_texture( underlying(texture) );
}

inline void active_texture(GLenum texture)
{
	::gl::active_texture(texture);
}

//------------------------------------------------------------------------------
inline void tex_image_1d(GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void* pixels)
{
	::gl::tex_image_1d(target, level, internalformat, width, border, format, type, pixels);
}
inline void tex_image_2d(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void* pixels)
{
	::gl::tex_image_2d(target, level, internalformat, width, height, border, format, type, pixels);
}
inline void tex_image_3d(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void * pixels)
{
	::gl::tex_image_3d(target, level, internalformat, width, height, depth, border, format, type, pixels);
}

inline void copy_tex_image_1d(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border)
{
	::gl::copy_tex_image_1d(target, level, internalformat, x, y, width, border);
}
inline void copy_tex_image_2d(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border)
{
	::gl::copy_tex_image_2d(target, level, internalformat, x, y, width, height, border);
}

inline void tex_image_2d_multisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations)
{
	::gl::tex_image_2d_multisample(target, samples, internalformat, width, height, fixedsamplelocations);
}
inline void tex_image_3d_multisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations)
{
	::gl::tex_image_3d_multisample(target, samples, internalformat, width, height, depth, fixedsamplelocations);
}
//------------------------------------------------------------------------------
inline void tex_parameter(GLenum target, GLenum pname, GLfloat param)
{
	::gl::tex_parameter_f(target, pname, param);
}
inline void tex_parameter(GLenum target, GLenum pname, const GLfloat* params)
{
	::gl::tex_parameter_fv(target, pname, params);
}
inline void tex_parameter(GLenum target, GLenum pname, GLint param)
{
	::gl::tex_parameter_i(target, pname, param);
}
inline void tex_parameter(GLenum target, GLenum pname, const GLint* params)
{
	::gl::tex_parameter_iv(target, pname, params);
}
inline void tex_parameter_i(GLenum target, GLenum pname, const GLint* params)
{
	::gl::tex_parameter_i_iv(target, pname, params);
}
inline void tex_parameter_i(GLenum target, GLenum pname, const GLuint* params)
{
	::gl::tex_parameter_i_uiv(target, pname, params);
}
//------------------------------------------------------------------------------
inline void tex_sub_image_1d(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void * pixels)
{
	::gl::tex_sub_image_1d(target, level, xoffset, width, format, type, pixels);
}
inline void tex_sub_image_2d(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void * pixels)
{
	::gl::tex_sub_image_2d(target, level, xoffset, yoffset, width, height, format, type, pixels);
}
inline void tex_sub_image_3d(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void * pixels)
{
	::gl::tex_sub_image_3d(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
}

inline void copy_tex_sub_image_1d(GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width)
{
	::gl::copy_tex_sub_image_1d(target, level, xoffset, x, y, width);
}
inline void copy_tex_sub_image_2d(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
	::gl::copy_tex_sub_image_2d(target, level, xoffset, yoffset, x, y, width, height);
}
inline void copy_tex_sub_image_3d(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
	::gl::copy_tex_sub_image_3d(target, level, xoffset, yoffset, zoffset, x, y, width, height);
}

//------------------------------------------------------------------------------
inline void compressed_tex_image_1d(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void * data)
{
	::gl::compressed_tex_image_1d(target, level, internalformat, width, border, imageSize, data);
}
inline void compressed_tex_image_2d(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void * data)
{
	::gl::compressed_tex_image_2d(target, level, internalformat, width, height, border, imageSize, data);
}
inline void compressed_tex_image_3d(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void * data)
{
	::gl::compressed_tex_image_3d(target, level, internalformat, width, height, depth, border, imageSize, data);
}
inline void compressed_tex_sub_image_1d(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void * data)
{
	::gl::compressed_tex_sub_image_1d(target, level, xoffset, width, format, imageSize, data);
}
inline void compressed_tex_sub_image_2d(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void * data)
{
	::gl::compressed_tex_sub_image_2d(target, level, xoffset, yoffset, width, height, format, imageSize, data);
}
inline void compressed_tex_sub_image_3d(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void * data)
{
	::gl::compressed_tex_sub_image_3d(target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);
}

//------------------------------------------------------------------------------
inline void get_tex_image(GLenum target, GLint level, GLenum format, GLenum type, void * pixels)
{
	::gl::get_tex_image(target, level, format, type, pixels);
}
inline void get_compressed_tex_image(GLenum target, GLint level, void * img)
{
	::gl::get_compressed_tex_image(target, level, img);
}
//------------------------------------------------------------------------------
inline void get_tex_level_parameter(GLenum target, GLint level, GLenum pname, GLfloat * params)
{
	::gl::get_tex_level_parameter_fv(target, level, pname, params);
}
inline void get_tex_level_parameter(GLenum target, GLint level, GLenum pname, GLint * params)
{
	::gl::get_tex_level_parameter_iv(target, level, pname, params);
}
inline void get_tex_parameter(GLenum target, GLenum pname, GLfloat * params)
{
	::gl::get_tex_parameter_fv(target, pname, params);
}
inline void get_tex_parameter(GLenum target, GLenum pname, GLint * params)
{
	::gl::get_tex_parameter_iv(target, pname, params);
}
} // namespace aw::gl

#endif//aw_graphics_awgl_texture_func_h
