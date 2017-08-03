/*
 * Copyright (C) 2016  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <aw/graphics/gl/shader.h>
#include <aw/graphics/gl/awgl/shader_func.h>
#include <iostream> // temporary
#include <vector>

namespace aw::gl3 {

namespace {
// TODO: move to aw::gl
void report_info_log( shader_handle shd )
{
	GLint length;
	gl::get_shader(shd, gl::shader_param::info_log_length, &length);

	std::vector<char> log(length + 1);
	gl::get_info_log(shd, log.size(), nullptr, log.data());

	// TODO: gl3::journal
	std::cerr << string_view{log.data(), log.size()} << '\n';
}
} // namespace

shader::shader(gl::shader_type type)
{
	_shader = gl::create_shader( type );
}

void shader::cleanup()
{
	gl::delete_shader(_shader);
	_shader = gl::no_shader;
}

gl::shader_type shader::type() const
{
	GLint type;
	gl::get_shader( _shader, gl::shader_param::type, &type );
	return gl::shader_type(type);
}

bool shader::is_compiled() const
{
	if (!_shader) return false;
	GLint status;
	gl::get_shader( _shader, gl::shader_param::compile_status, &status );
	return status == GL_TRUE;
}

bool shader::compile(string_view code)
{
	char const* data = code.data();
	GLint length     = GLint(code.size());

	gl::shader_source( _shader, 1, &data, &length );
	gl::compile_shader( _shader );

	bool status = is_compiled();
	if (status == false) {
		std::cout << "Failed to compile " << enum_string( type() ) << " shader:" << '\n';
		report_info_log( _shader );
	}

	return status;
}

shader::operator shader_handle()
{
	return _shader;
}

} // namespace aw::gl3
