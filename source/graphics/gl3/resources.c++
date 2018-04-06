/*
 * Copyright (C) 2017  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <aw/graphics/gl/material_manager.h>
#include <aw/graphics/gl/awgl/shader_func.h>
#include <aw/graphics/gl/utility/program_loader.h>
#include <aw/fileformat/png/reader.h>
#include <aw/fileformat/png/log.h>
#include <aw/log/ostream_logger.h>
#include <aw/io/input_file_stream.h>

#include <iostream>

namespace aw::gl3 {
aw::ostream_logger ologger{std::cerr};
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

// TEMPORARY
size_t texture_manager::create_texture_array( array_view<string_view> names )
{
	png::log.set_logger(&ologger);
	png::image img;
	std::optional<png::image> tmp;
	for (auto name : names) {
		io::input_file_stream ts{name};

		tmp = png::read(ts);
		if (!tmp)
			return -1;
		img.width  = tmp->width;
		img.height = tmp->height;
		img.data.insert( img.data.end(), tmp->data.begin(), tmp->data.end() );
	}

	return add_resource( names[0], texture{ img.data, names.size(), img.width, img.height} );
}
} // namespace aw::gl3
