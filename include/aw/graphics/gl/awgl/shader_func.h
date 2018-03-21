/*
 * Copyright (C) 2016  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_graphics_awgl_shader_func_h
#define aw_graphics_awgl_shader_func_h
#include <aw/graphics/gl/api/gl_33.h>
#include <aw/graphics/gl/awgl/shader_enum.h>
#include <aw/types/enum.h>
namespace aw {
namespace gl {
//------------------------------------------------------------------------------
inline shader_handle create_shader(shader_type type)
{
	return shader_handle{ ::gl::create_shader( underlying(type) ) };
}
inline void delete_shader(shader_handle shader)
{
	::gl::delete_shader( underlying(shader) );
}

inline void attach_shader(program_handle program, shader_handle shader)
{
	::gl::attach_shader( underlying(program), underlying(shader) );
}
inline void detach_shader(program_handle program, shader_handle shader)
{
	::gl::detach_shader( underlying(program), underlying(shader) );
}

inline void compile_shader(shader_handle shader)
{
	::gl::compile_shader( underlying(shader) );
}

inline void get_shader(shader_handle shader, shader_param pname, GLint* params)
{
	::gl::get_shader_iv( underlying(shader), underlying(pname), params);
}

inline void get_info_log(shader_handle shader, GLsizei bufSize, GLsizei* length, GLchar* infoLog)
{
	::gl::get_shader_info_log( underlying(shader), bufSize, length, infoLog);
}

inline void shader_source(shader_handle shader, GLsizei count, const GLchar* const* string, const GLint* length)
{
	::gl::shader_source( underlying(shader), count, string, length);
}
//------------------------------------------------------------------------------
inline program_handle create_program()
{
	return program_handle{ ::gl::create_program() };
}
inline void delete_program(program_handle program)
{
	::gl::delete_program( underlying(program) );
}

inline void link_program(program_handle program)
{
	::gl::link_program( underlying(program) );
}

inline void validate_program(program_handle program)
{
	::gl::validate_program( underlying(program) );
}

inline void use_program(program_handle program)
{
	::gl::use_program( underlying(program) );
}

inline void get_program(program_handle program, program_param pname, GLint* params)
{
	::gl::get_program_iv(underlying(program), underlying(pname), params);
}

inline void get_info_log(program_handle program, GLsizei bufSize, GLsizei* length, GLchar* infoLog)
{
	::gl::get_program_info_log(underlying(program), bufSize, length, infoLog);
}

//------------------------------------------------------------------------------
inline GLboolean is_program(GLuint program)
{
	return ::gl::is_program(program);
}
inline GLboolean is_shader(GLuint shader)
{
	return ::gl::is_shader(shader);
}
inline GLboolean is_program(program_handle program)
{
	return is_program(underlying(program));
}
inline GLboolean is_shader(shader_handle shader)
{
	return is_shader(underlying(shader));
}

//------------------------------------------------------------------------------
inline uniform_location get_uniform_location(program_handle program, const GLchar* name)
{
	return uniform_location{
		::gl::get_uniform_location(underlying(program), name)
	};
}

inline void get_uniform(GLuint program, GLint location, GLfloat * params)
{
	::gl::get_uniform_fv(program, location, params);
}
inline void get_uniform(GLuint program, GLint location, GLint * params)
{
	::gl::get_uniform_iv(program, location, params);
}
inline void get_uniform(program_handle program, uniform_location location, GLuint* params)
{
	::gl::get_uniform_uiv( underlying(program), underlying(location), params);
}

//------------------------------------------------------------------------------
inline void uniform_1f(uniform_location location, GLfloat v0)
{
	::gl::uniform_1f( underlying(location), v0);
}
inline void uniform_1fv(uniform_location location, GLsizei count, const GLfloat* value)
{
	::gl::uniform_1fv( underlying(location), count, value);
}
inline void uniform_1i(uniform_location location, GLint v0)
{
	::gl::uniform_1i( underlying(location), v0);
}
inline void uniform_1iv(uniform_location location, GLsizei count, const GLint* value)
{
	::gl::uniform_1iv( underlying(location), count, value);
}
inline void uniform_2f(uniform_location location, GLfloat v0, GLfloat v1)
{
	::gl::uniform_2f( underlying(location), v0, v1);
}
inline void uniform_2fv(uniform_location location, GLsizei count, const GLfloat* value)
{
	::gl::uniform_2fv( underlying(location), count, value);
}
inline void uniform_2i(uniform_location location, GLint v0, GLint v1)
{
	::gl::uniform_2i( underlying(location), v0, v1);
}
inline void uniform_2iv(uniform_location location, GLsizei count, const GLint* value)
{
	::gl::uniform_2iv( underlying(location), count, value);
}
inline void uniform_3f(uniform_location location, GLfloat v0, GLfloat v1, GLfloat v2)
{
	::gl::uniform_3f( underlying(location), v0, v1, v2);
}
inline void uniform_3fv(uniform_location location, GLsizei count, const GLfloat* value)
{
	::gl::uniform_3fv( underlying(location), count, value);
}
inline void uniform_3i(uniform_location location, GLint v0, GLint v1, GLint v2)
{
	::gl::uniform_3i( underlying(location), v0, v1, v2);
}
inline void uniform_3iv(uniform_location location, GLsizei count, const GLint* value)
{
	::gl::uniform_3iv( underlying(location), count, value);
}
inline void uniform_4f(uniform_location location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
	::gl::uniform_4f( underlying(location), v0, v1, v2, v3);
}
inline void uniform_4fv(uniform_location location, GLsizei count, const GLfloat* value)
{
	::gl::uniform_4fv( underlying(location), count, value);
}

inline void uniform_4i(uniform_location location, GLint v0, GLint v1, GLint v2, GLint v3)
{
	::gl::uniform_4i( underlying(location), v0, v1, v2, v3);
}
inline void uniform_4iv(uniform_location location, GLsizei count, const GLint* value)
{
	::gl::uniform_4iv( underlying(location), count, value);
}
inline void uniform_1ui(uniform_location location, GLuint v0)
{
	::gl::uniform_1ui( underlying(location), v0);
}
inline void uniform_1uiv(uniform_location location, GLsizei count, const GLuint * value)
{
	::gl::uniform_1uiv( underlying(location), count, value);
}
inline void uniform_2ui(uniform_location location, GLuint v0, GLuint v1)
{
	::gl::uniform_2ui( underlying(location), v0, v1);
}
inline void uniform_2uiv(uniform_location location, GLsizei count, const GLuint * value)
{
	::gl::uniform_2uiv( underlying(location), count, value);
}
inline void uniform_3ui(uniform_location location, GLuint v0, GLuint v1, GLuint v2)
{
	::gl::uniform_3ui( underlying(location), v0, v1, v2);
}
inline void uniform_3uiv(uniform_location location, GLsizei count, const GLuint * value)
{
	::gl::uniform_3uiv( underlying(location), count, value);
}
inline void uniform_4ui(uniform_location location, GLuint v0, GLuint v1, GLuint v2, GLuint v3)
{
	::gl::uniform_4ui( underlying(location), v0, v1, v2, v3);
}
inline void uniform_4uiv(uniform_location location, GLsizei count, const GLuint * value)
{
	::gl::uniform_4uiv( underlying(location), count, value);
}


inline void uniform_matrix_2fv(uniform_location location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
	::gl::uniform_matrix_2fv( underlying(location), count, transpose, value);
}
inline void uniform_matrix_3fv(uniform_location location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
	::gl::uniform_matrix_3fv( underlying(location), count, transpose, value);
}
inline void uniform_matrix_4fv(uniform_location location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
	::gl::uniform_matrix_4fv( underlying(location), count, transpose, value);
}

inline void uniform_matrix_2x3fv(uniform_location location, GLsizei count, GLboolean transpose, const GLfloat * value)
{
	::gl::uniform_matrix_2x3fv( underlying(location), count, transpose, value);
}
inline void uniform_matrix_2x4fv(uniform_location location, GLsizei count, GLboolean transpose, const GLfloat * value)
{
	::gl::uniform_matrix_2x4fv( underlying(location), count, transpose, value);
}
inline void uniform_matrix_3x2fv(uniform_location location, GLsizei count, GLboolean transpose, const GLfloat * value)
{
	::gl::uniform_matrix_3x2fv( underlying(location), count, transpose, value);
}
inline void uniform_matrix_3x4fv(uniform_location location, GLsizei count, GLboolean transpose, const GLfloat * value)
{
	::gl::uniform_matrix_3x4fv( underlying(location), count, transpose, value);
}
inline void uniform_matrix_4x2fv(uniform_location location, GLsizei count, GLboolean transpose, const GLfloat * value)
{
	::gl::uniform_matrix_4x2fv( underlying(location), count, transpose, value);
}
inline void uniform_matrix_4x3fv(uniform_location location, GLsizei count, GLboolean transpose, const GLfloat * value)
{
	::gl::uniform_matrix_4x3fv( underlying(location), count, transpose, value);
}

//------------------------------------------------------------------------------
inline uniform_block_index get_uniform_block_index(program_handle program, const GLchar* uniformBlockName)
{
	return uniform_block_index{
		::gl::get_uniform_block_index( underlying(program), uniformBlockName)
	};
}

inline void uniform_block_binding(program_handle program, uniform_block_index uniformBlockIndex, GLuint uniformBlockBinding)
{
	::gl::uniform_block_binding(underlying(program), underlying(uniformBlockIndex), uniformBlockBinding);
}
} // namespace gl
} // namespace aw
#endif//aw_graphics_awgl_shader_func_h
