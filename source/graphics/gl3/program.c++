/*
 * Copyright (C) 2016  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <aw/graphics/gl/program.h>
#include <aw/graphics/gl/shader.h>
#include <aw/graphics/gl/awgl/shader_func.h>
#include <aw/utility/on_scope_exit.h>
#include <aw/types/enum.h>
#include <iostream> // temporary
#include <vector>

namespace aw::gl3 {
namespace {
void report_info_log( program_handle _program)
{
	GLint length;
	gl::get_programiv( _program, gl::program_param::info_log_length, &length );

	std::vector<char> log(length + 1);
	gl::get_info_log( _program, log.size(), nullptr, log.data() );

	std::cerr << string_view{log.data(), log.size()} << '\n';
}
} // namespace

program::program()
{
	_program = gl::create_program();
}

void program::cleanup()
{
	gl::delete_program(_program);
	_program = gl::no_program;
}

bool program::is_linked() const
{
	if (!_program) return false;

	GLint status;
	gl::get_programiv(_program, gl::program_param::link_status, &status);

	return status == GL_TRUE;
}

bool program::link(array_ref<shader> shaders)
{
	for ( auto& shader : shaders )
		gl::attach_shader( _program, shader_handle{shader});

	gl::link_program( _program );

	bool status = is_linked();
	if ( status == false ) {
		std::cerr << "Failed to link program: " << '\n';
		report_info_log( _program );
	}

	for ( auto& shader : shaders )
		gl::detach_shader( _program, shader_handle{shader});

	return status;
}

uniform_location program::uniform( char const* name )
{
	return gl::get_uniform_location( _program, name );
}

uniform_block_index program::uniform_block( char const* name )
{
	return gl::get_uniform_block_index( _program, name );
}

program::operator program_handle()
{
	return program_handle{_program};
}

} // namespace aw::gl3
