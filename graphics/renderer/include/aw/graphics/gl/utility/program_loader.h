/*
 * Copyright (C) 2016-2018  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_graphics_gl3_shader_file_h
#define aw_graphics_gl3_shader_file_h
#include <aw/graphics/gl/program.h>
#include <aw/io/file.h>
#include <aw/types/optional.h>
#include <vector>
namespace aw {
namespace gl3 {
inline optional<shader> compile_shader( gl::shader_type type, string_view contents )
{
	shader shd{ type };
	if (!shd.compile( contents ))
		return nullopt;
	return {std::move(shd)};
}

inline optional<shader> load_shader( gl::shader_type type, fs::path const& path )
{
	std::vector<char> buf;
	try {
		io::file file{ path, io::file_mode::read };
		buf.resize( file.size() );
		file.read( buf.data(), buf.size() );
	} catch( std::exception& ex ) {
		// TODO: journal.error( "gl3", ex.what() );
		return nullopt;
	}

	return compile_shader( type, string_view{buf.data(), buf.size()} );
}

inline optional<program> link_program( array_ref<shader> shader_list )
{
	gl3::program program;
	bool linked = program.link( shader_list );
	if (!linked)
		return std::nullopt;
	return {std::move(program)};
}

inline optional<program> load_program( string_view v, string_view f )
{
	std::vector<shader> shader_list;

	auto vsh = load_shader( gl::shader_type::vertex,   v );
	auto fsh = load_shader( gl::shader_type::fragment, f );

	if (vsh && fsh) {
		shader_list.push_back(std::move(*vsh));
		shader_list.push_back(std::move(*fsh));
	}

	return link_program(shader_list);
}
} // namespace gl3
} // namespace aw
#endif//aw_graphics_gl3_shader_file_h
