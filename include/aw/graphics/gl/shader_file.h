/*
 * Copyright (C) 2016  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_graphics_gl3_shader_file_h
#define aw_graphics_gl3_shader_file_h
#include <aw/graphics/gl/shader.h>
#include <aw/io/file.h>
#include <aw/types/optional.h>
#include <vector>
namespace aw {
namespace gl3 {

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

	shader shd{ type };
	if (!shd.compile( string_view{buf.data(), buf.size()} ))
		return nullopt;
	return shd;
}



} // namespace gl3
} // namespace aw
#endif//aw_graphics_gl3_shader_file_h
