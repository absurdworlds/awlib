/*
 * Copyright (C) 2016  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <aw/graphics/gl/shader.h>
#include <aw/graphics/gl/gl_ext33.h>
#include <iostream> // temporary
namespace aw::gl3 {
static_assert(GLenum(gl::shader_type::fragment) == GL_FRAGMENT_SHADER);
static_assert(GLenum(gl::shader_type::vertex)   == GL_VERTEX_SHADER);
static_assert(GLenum(gl::shader_type::geometry) == GL_GEOMETRY_SHADER);


namespace {
// TODO: just had an idea of replacing some of inline gl_ext functions
// with my own wrappers, doing some convenience stuff
void report_shader_info_log(gl::shader_type type, GLuint _shader)
{
	GLint length;
	gl::get_shaderiv(_shader, GL_INFO_LOG_LENGTH, &length);

	std::vector<char> info_log(length + 1);
	gl::get_shader_info_log(_shader, length, NULL, info_log.data());

	// TODO: gl3::journal
	std::cerr << string_view{info_log.data(), info_log.size()} << '\n';
}
} // namespace

shader::~shader()
{
	if (_shader)
		gl::delete_shader(_shader);
}

optional<shader> shader::compile(gl::shader_type type, string_view code)
{
	char const* data = code.data();
	GLint length     = GLint(code.size());

	GLuint _shader = gl::create_shader( GLenum(type) );
	gl::shader_source( _shader, 1, &data, &length );
	gl::compile_shader( _shader );

	GLint status;
	gl::get_shaderiv( _shader, GL_COMPILE_STATUS, &status );
	if (status == GL_FALSE) {
		std::cout << "Failed to compile " << enum_string( type ) << " shader:" << '\n';
		report_shader_info_log(type, _shader);
		gl::delete_shader(_shader);
		return nullopt;
	}

	return {_shader};
}

} // namespace aw::gl3
