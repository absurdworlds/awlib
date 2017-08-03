/*
 * Copyright (C) 2016  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_graphics_awgl_gl_func_h
#define aw_graphics_awgl_gl_func_h
#include <aw/graphics/gl/api/gl_33.h>
#include <aw/types/enum.h>
namespace aw {
namespace gl {
/* gl version 1.0 */
inline void blend_func(GLenum sfactor, GLenum dfactor)
{
	::gl::blend_func(sfactor, dfactor);
}
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
inline void color_mask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)
{
	::gl::color_mask(red, green, blue, alpha);
}
inline void cull_face(GLenum mode)
{
	::gl::cull_face(mode);
}
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
inline void disable(GLenum cap)
{
	::gl::disable(cap);
}
inline void draw_buffer(GLenum buf)
{
	::gl::draw_buffer(buf);
}
inline void enable(GLenum cap)
{
	::gl::enable(cap);
}
inline void finish(void)
{
	::gl::finish();
}
inline void flush(void)
{
	::gl::flush();
}
inline void front_face(GLenum mode)
{
	::gl::front_face(mode);
}
inline void get_boolean_v(GLenum pname, GLboolean * data)
{
	::gl::get_boolean_v(pname, data);
}
inline void get_double_v(GLenum pname, GLdouble * data)
{
	::gl::get_double_v(pname, data);
}
inline GLenum get_error(void)
{
	return ::gl::get_error();
}
inline void get_floatv(GLenum pname, GLfloat * data)
{
	::gl::get_floatv(pname, data);
}
inline void get_integerv(GLenum pname, GLint * data)
{
	::gl::get_integerv(pname, data);
}
inline const GLubyte * get_string(GLenum name)
{
	return ::gl::get_string(name);
}

inline void hint(GLenum target, GLenum mode)
{
	::gl::hint(target, mode);
}
inline GLboolean is_enabled(GLenum cap)
{
	return ::gl::is_enabled(cap);
}
inline void line_width(GLfloat width)
{
	::gl::line_width(width);
}
inline void logic_op(GLenum opcode)
{
	::gl::logic_op(opcode);
}
inline void pixel_storef(GLenum pname, GLfloat param)
{
	::gl::pixel_storef(pname, param);
}
inline void pixel_storei(GLenum pname, GLint param)
{
	::gl::pixel_storei(pname, param);
}
inline void point_size(GLfloat size)
{
	::gl::point_size(size);
}
inline void polygon_mode(GLenum face, GLenum mode)
{
	::gl::polygon_mode(face, mode);
}
inline void read_buffer(GLenum src)
{
	::gl::read_buffer(src);
}
inline void read_pixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void * pixels)
{
	::gl::read_pixels(x, y, width, height, format, type, pixels);
}
inline void scissor(GLint x, GLint y, GLsizei width, GLsizei height)
{
	::gl::scissor(x, y, width, height);
}
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

inline void viewport(GLint x, GLint y, GLsizei width, GLsizei height)
{
	::gl::viewport(x, y, width, height);
}

/* gl version 1.1 */

inline void draw_arrays(GLenum mode, GLint first, GLsizei count)
{
	::gl::draw_arrays(mode, first, count);
}
inline void draw_elements(GLenum mode, GLsizei count, GLenum type, const void * indices)
{
	::gl::draw_elements(mode, count, type, indices);
}

inline void polygon_offset(GLfloat factor, GLfloat units)
{
	::gl::polygon_offset(factor, units);
}


/* gl version 1.2 */
inline void draw_range_elements(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void * indices)
{
	::gl::draw_range_elements(mode, start, end, count, type, indices);
}

/* gl version 1.3 */

inline void sample_coverage(GLfloat value, GLboolean invert)
{
	::gl::sample_coverage(value, invert);
}

/* gl version 1.4 */
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
inline void multi_draw_arrays(GLenum mode, const GLint * first, const GLsizei * count, GLsizei drawcount)
{
	::gl::multi_draw_arrays(mode, first, count, drawcount);
}
inline void multi_draw_elements(GLenum mode, const GLsizei * count, GLenum type, const void *const* indices, GLsizei drawcount)
{
	::gl::multi_draw_elements(mode, count, type, indices, drawcount);
}
inline void point_parameterf(GLenum pname, GLfloat param)
{
	::gl::point_parameterf(pname, param);
}
inline void point_parameterfv(GLenum pname, const GLfloat * params)
{
	::gl::point_parameterfv(pname, params);
}
inline void point_parameteri(GLenum pname, GLint param)
{
	::gl::point_parameteri(pname, param);
}
inline void point_parameteriv(GLenum pname, const GLint * params)
{
	::gl::point_parameteriv(pname, params);
}

/* gl version 1.5 */
inline void begin_query(GLenum target, GLuint id)
{
	::gl::begin_query(target, id);
}


inline void delete_queries(GLsizei n, const GLuint * ids)
{
	::gl::delete_queries(n, ids);
}
inline void end_query(GLenum target)
{
	::gl::end_query(target);
}
inline void gen_queries(GLsizei n, GLuint * ids)
{
	::gl::gen_queries(n, ids);
}
inline void get_query_objectiv(GLuint id, GLenum pname, GLint * params)
{
	::gl::get_query_objectiv(id, pname, params);
}
inline void get_query_objectuiv(GLuint id, GLenum pname, GLuint * params)
{
	::gl::get_query_objectuiv(id, pname, params);
}
inline void get_queryiv(GLenum target, GLenum pname, GLint * params)
{
	::gl::get_queryiv(target, pname, params);
}

inline GLboolean is_query(GLuint id)
{
	return ::gl::is_query(id);
}


/* gl version 2.0 */

inline void blend_equation_separate(GLenum modeRGB, GLenum modeAlpha)
{
	::gl::blend_equation_separate(modeRGB, modeAlpha);
}
inline void draw_buffers(GLsizei n, const GLenum * bufs)
{
	::gl::draw_buffers(n, bufs);
}

inline void get_active_attrib(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name)
{
	::gl::get_active_attrib(program, index, bufSize, length, size, type, name);
}
inline void get_active_uniform(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name)
{
	::gl::get_active_uniform(program, index, bufSize, length, size, type, name);
}
inline void get_attached_shaders(GLuint program, GLsizei maxCount, GLsizei * count, GLuint * shaders)
{
	::gl::get_attached_shaders(program, maxCount, count, shaders);
}
inline GLint get_attrib_location(GLuint program, const GLchar * name)
{
	return ::gl::get_attrib_location(program, name);
}

inline void get_shader_source(GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * source)
{
	::gl::get_shader_source(shader, bufSize, length, source);
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


/* gl version 2.1 */


/* gl version 3.0 */
inline void begin_conditional_render(GLuint id, GLenum mode)
{
	::gl::begin_conditional_render(id, mode);
}
inline void begin_transform_feedback(GLenum primitiveMode)
{
	::gl::begin_transform_feedback(primitiveMode);
}

inline void bind_frag_data_location(GLuint program, GLuint color, const GLchar * name)
{
	::gl::bind_frag_data_location(program, color, name);
}
inline void bind_framebuffer(GLenum target, GLuint framebuffer)
{
	::gl::bind_framebuffer(target, framebuffer);
}
inline void bind_renderbuffer(GLenum target, GLuint renderbuffer)
{
	::gl::bind_renderbuffer(target, renderbuffer);
}

inline void blit_framebuffer(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter)
{
	::gl::blit_framebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
}
inline GLenum check_framebuffer_status(GLenum target)
{
	return ::gl::check_framebuffer_status(target);
}
inline void clamp_color(GLenum target, GLenum clamp)
{
	::gl::clamp_color(target, clamp);
}
inline void clear_bufferfi(GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil)
{
	::gl::clear_bufferfi(buffer, drawbuffer, depth, stencil);
}
inline void clear_bufferfv(GLenum buffer, GLint drawbuffer, const GLfloat * value)
{
	::gl::clear_bufferfv(buffer, drawbuffer, value);
}
inline void clear_bufferiv(GLenum buffer, GLint drawbuffer, const GLint * value)
{
	::gl::clear_bufferiv(buffer, drawbuffer, value);
}
inline void clear_bufferuiv(GLenum buffer, GLint drawbuffer, const GLuint * value)
{
	::gl::clear_bufferuiv(buffer, drawbuffer, value);
}
inline void color_maski(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a)
{
	::gl::color_maski(index, r, g, b, a);
}
inline void delete_framebuffers(GLsizei n, const GLuint * framebuffers)
{
	::gl::delete_framebuffers(n, framebuffers);
}
inline void delete_renderbuffers(GLsizei n, const GLuint * renderbuffers)
{
	::gl::delete_renderbuffers(n, renderbuffers);
}

inline void disablei(GLenum target, GLuint index)
{
	::gl::disablei(target, index);
}
inline void enablei(GLenum target, GLuint index)
{
	::gl::enablei(target, index);
}
inline void end_conditional_render(void)
{
	::gl::end_conditional_render();
}
inline void end_transform_feedback(void)
{
	::gl::end_transform_feedback();
}
inline void flush_mapped_buffer_range(GLenum target, GLintptr offset, GLsizeiptr length)
{
	::gl::flush_mapped_buffer_range(target, offset, length);
}
inline void framebuffer_renderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer)
{
	::gl::framebuffer_renderbuffer(target, attachment, renderbuffertarget, renderbuffer);
}
inline void framebuffer_texture1_d(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
{
	::gl::framebuffer_texture1_d(target, attachment, textarget, texture, level);
}
inline void framebuffer_texture2_d(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
{
	::gl::framebuffer_texture2_d(target, attachment, textarget, texture, level);
}
inline void framebuffer_texture3_d(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset)
{
	::gl::framebuffer_texture3_d(target, attachment, textarget, texture, level, zoffset);
}
inline void framebuffer_texture_layer(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer)
{
	::gl::framebuffer_texture_layer(target, attachment, texture, level, layer);
}
inline void gen_framebuffers(GLsizei n, GLuint * framebuffers)
{
	::gl::gen_framebuffers(n, framebuffers);
}
inline void gen_renderbuffers(GLsizei n, GLuint * renderbuffers)
{
	::gl::gen_renderbuffers(n, renderbuffers);
}

inline void generate_mipmap(GLenum target)
{
	::gl::generate_mipmap(target);
}
inline void get_booleani_v(GLenum target, GLuint index, GLboolean * data)
{
	::gl::get_booleani_v(target, index, data);
}
inline GLint get_frag_data_location(GLuint program, const GLchar * name)
{
	return ::gl::get_frag_data_location(program, name);
}
inline void get_framebuffer_attachment_parameteriv(GLenum target, GLenum attachment, GLenum pname, GLint * params)
{
	::gl::get_framebuffer_attachment_parameteriv(target, attachment, pname, params);
}
inline void get_integeri_v(GLenum target, GLuint index, GLint * data)
{
	::gl::get_integeri_v(target, index, data);
}
inline void get_renderbuffer_parameteriv(GLenum target, GLenum pname, GLint * params)
{
	::gl::get_renderbuffer_parameteriv(target, pname, params);
}
inline const GLubyte * get_stringi(GLenum name, GLuint index)
{
	return ::gl::get_stringi(name, index);
}
inline void get_tex_parameter_iiv(GLenum target, GLenum pname, GLint * params)
{
	::gl::get_tex_parameter_iiv(target, pname, params);
}
inline void get_tex_parameter_iuiv(GLenum target, GLenum pname, GLuint * params)
{
	::gl::get_tex_parameter_iuiv(target, pname, params);
}
inline void get_transform_feedback_varying(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLsizei * size, GLenum * type, GLchar * name)
{
	::gl::get_transform_feedback_varying(program, index, bufSize, length, size, type, name);
}


inline GLboolean is_enabled_i(GLenum target, GLuint index)
{
	return ::gl::is_enabledi(target, index);
}
inline GLboolean is_framebuffer(GLuint framebuffer)
{
	return ::gl::is_framebuffer(framebuffer);
}
inline GLboolean is_renderbuffer(GLuint renderbuffer)
{
	return ::gl::is_renderbuffer(renderbuffer);
}

inline void * map_buffer_range(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access)
{
	return ::gl::map_buffer_range(target, offset, length, access);
}
inline void renderbuffer_storage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height)
{
	::gl::renderbuffer_storage(target, internalformat, width, height);
}
inline void renderbuffer_storage_multisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height)
{
	::gl::renderbuffer_storage_multisample(target, samples, internalformat, width, height);
}

inline void transform_feedback_varyings(GLuint program, GLsizei count, const GLchar *const* varyings, GLenum bufferMode)
{
	::gl::transform_feedback_varyings(program, count, varyings, bufferMode);
}

/* gl version 3.1 */
inline void copy_buffer_sub_data(GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size)
{
	::gl::copy_buffer_sub_data(readTarget, writeTarget, readOffset, writeOffset, size);
}
inline void draw_arrays_instanced(GLenum mode, GLint first, GLsizei count, GLsizei instancecount)
{
	::gl::draw_arrays_instanced(mode, first, count, instancecount);
}
inline void draw_elements_instanced(GLenum mode, GLsizei count, GLenum type, const void * indices, GLsizei instancecount)
{
	::gl::draw_elements_instanced(mode, count, type, indices, instancecount);
}
inline void get_active_uniform_block_name(GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei * length, GLchar * uniformBlockName)
{
	::gl::get_active_uniform_block_name(program, uniformBlockIndex, bufSize, length, uniformBlockName);
}
inline void get_active_uniform_blockiv(GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint * params)
{
	::gl::get_active_uniform_blockiv(program, uniformBlockIndex, pname, params);
}
inline void get_active_uniform_name(GLuint program, GLuint uniformIndex, GLsizei bufSize, GLsizei * length, GLchar * uniformName)
{
	::gl::get_active_uniform_name(program, uniformIndex, bufSize, length, uniformName);
}
inline void get_active_uniformsiv(GLuint program, GLsizei uniformCount, const GLuint * uniformIndices, GLenum pname, GLint * params)
{
	::gl::get_active_uniformsiv(program, uniformCount, uniformIndices, pname, params);
}

inline void get_uniform_indices(GLuint program, GLsizei uniformCount, const GLchar *const* uniformNames, GLuint * uniformIndices)
{
	::gl::get_uniform_indices(program, uniformCount, uniformNames, uniformIndices);
}
inline void primitive_restart_index(GLuint index)
{
	::gl::primitive_restart_index(index);
}
inline void tex_buffer(GLenum target, GLenum internalformat, GLuint buffer)
{
	::gl::tex_buffer(target, internalformat, buffer);
}


/* gl version 3.2 */
inline GLenum client_wait_sync(GLsync sync, GLbitfield flags, GLuint64 timeout)
{
	return ::gl::client_wait_sync(sync, flags, timeout);
}
inline void delete_sync(GLsync sync)
{
	::gl::delete_sync(sync);
}
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
inline GLsync fence_sync(GLenum condition, GLbitfield flags)
{
	return ::gl::fence_sync(condition, flags);
}
inline void framebuffer_texture(GLenum target, GLenum attachment, GLuint texture, GLint level)
{
	::gl::framebuffer_texture(target, attachment, texture, level);
}
inline void get_buffer_parameteri64v(GLenum target, GLenum pname, GLint64 * params)
{
	::gl::get_buffer_parameteri64v(target, pname, params);
}
inline void get_integer64i_v(GLenum target, GLuint index, GLint64 * data)
{
	::gl::get_integer64i_v(target, index, data);
}
inline void get_integer64v(GLenum pname, GLint64 * data)
{
	::gl::get_integer64v(pname, data);
}
inline void get_multisamplefv(GLenum pname, GLuint index, GLfloat * val)
{
	::gl::get_multisamplefv(pname, index, val);
}
inline void get_synciv(GLsync sync, GLenum pname, GLsizei bufSize, GLsizei * length, GLint * values)
{
	::gl::get_synciv(sync, pname, bufSize, length, values);
}
inline GLboolean is_sync(GLsync sync)
{
	return ::gl::is_sync(sync);
}
inline void multi_draw_elements_base_vertex(GLenum mode, const GLsizei * count, GLenum type, const void *const* indices, GLsizei drawcount, const GLint * basevertex)
{
	::gl::multi_draw_elements_base_vertex(mode, count, type, indices, drawcount, basevertex);
}
inline void provoking_vertex(GLenum mode)
{
	::gl::provoking_vertex(mode);
}
inline void sample_maski(GLuint maskNumber, GLbitfield mask)
{
	::gl::sample_maski(maskNumber, mask);
}

inline void wait_sync(GLsync sync, GLbitfield flags, GLuint64 timeout)
{
	::gl::wait_sync(sync, flags, timeout);
}

/* gl version 3.3 */
inline void bind_frag_data_location_indexed(GLuint program, GLuint colorNumber, GLuint index, const GLchar * name)
{
	::gl::bind_frag_data_location_indexed(program, colorNumber, index, name);
}
inline void bind_sampler(GLuint unit, GLuint sampler)
{
	::gl::bind_sampler(unit, sampler);
}
inline void delete_samplers(GLsizei count, const GLuint * samplers)
{
	::gl::delete_samplers(count, samplers);
}
inline void gen_samplers(GLsizei count, GLuint * samplers)
{
	::gl::gen_samplers(count, samplers);
}
inline GLint get_frag_data_index(GLuint program, const GLchar * name)
{
	return ::gl::get_frag_data_index(program, name);
}
inline void get_query_object_i64v(GLuint id, GLenum pname, GLint64 * params)
{
	::gl::get_query_object_i64v(id, pname, params);
}
inline void get_query_object_ui64v(GLuint id, GLenum pname, GLuint64 * params)
{
	::gl::get_query_object_ui64v(id, pname, params);
}

inline void get_sampler_parameter_i(GLuint sampler, GLenum pname, GLint * params)
{
	::gl::get_sampler_parameter_i_iv(sampler, pname, params);
}
inline void get_sampler_parameter_i(GLuint sampler, GLenum pname, GLuint * params)
{
	::gl::get_sampler_parameter_i_uiv(sampler, pname, params);
}
inline void get_sampler_parameter(GLuint sampler, GLenum pname, GLfloat * params)
{
	::gl::get_sampler_parameterfv(sampler, pname, params);
}
inline void get_sampler_parameter(GLuint sampler, GLenum pname, GLint * params)
{
	::gl::get_sampler_parameter_iv(sampler, pname, params);
}

inline GLboolean is_sampler(GLuint sampler)
{
	return ::gl::is_sampler(sampler);
}

inline void query_counter(GLuint id, GLenum target)
{
	::gl::query_counter(id, target);
}

inline void sampler_parameter_i(GLuint sampler, GLenum pname, const GLint * param)
{
	::gl::sampler_parameter_i_iv(sampler, pname, param);
}
inline void sampler_parameter_i(GLuint sampler, GLenum pname, const GLuint * param)
{
	::gl::sampler_parameter_i_uiv(sampler, pname, param);
}
inline void sampler_parameter(GLuint sampler, GLenum pname, GLfloat param)
{
	::gl::sampler_parameter_f(sampler, pname, param);
}
inline void sampler_parameter(GLuint sampler, GLenum pname, const GLfloat * param)
{
	::gl::sampler_parameter_fv(sampler, pname, param);
}
inline void sampler_parameter(GLuint sampler, GLenum pname, GLint param)
{
	::gl::sampler_parameter_i(sampler, pname, param);
}
inline void sampler_parameter(GLuint sampler, GLenum pname, const GLint * param)
{
	::gl::sampler_parameter_iv(sampler, pname, param);
}


} //namespace gl
} // namespace aw
#endif//aw_graphics_awgl_shader_func_h
