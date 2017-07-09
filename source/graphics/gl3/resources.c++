/*
 * Copyright (C) 2017  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <aw/graphics/gl/material_manager.h>
#include <aw/graphics/gl/shader_file.h>
#include <aw/graphics/gl/awgl/shader_func.h>
#include <aw/fileformat/png/reader.h>
#include <aw/io/input_file_stream.h>

namespace aw::gl3 {
size_t program_manager::create_program( string_view v, string_view f )
{
	std::vector<shader> shaderList;

	auto vsh = load_shader( gl::shader_type::vertex,   v );
	auto fsh = load_shader( gl::shader_type::fragment, f );

	if (vsh && fsh) {
		shaderList.push_back(std::move(*vsh));
		shaderList.push_back(std::move(*fsh));
	}

	gl3::program program;
	bool linked = program.link( shaderList );
	if (!linked)
		return -1;

	return add_resource( v, std::move(program) );
}

size_t texture_manager::create_texture( string_view name )
{
	io::input_file_stream ts{name};

	auto img = png::read(ts);
	if (!img)
		return -1;

	return add_resource( name, texture{ img->data, img->width, img->height} );
}
} // namespace aw::gl3
