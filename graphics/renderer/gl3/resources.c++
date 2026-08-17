/*
 * Copyright (C) 2017  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <aw/graphics/gl/material_manager.h>
#include <aw/graphics/gl/log.h>
#include <aw/gl/wrapper/shader_func.h>
#include <aw/graphics/gl/utility/program_loader.h>
#include <aw/fileformat/png/reader.h>
#include <aw/io/input_file_stream.h>

namespace aw::gl3 {
size_t program_manager::create_program( array_view<shader_source> files )
{
	if (files.empty())
		return -1;

	std::vector<shader> shader_list;

	for (auto file : files)
	{
		auto shader = load_shader( file.type, file.path );
		if (shader)
			shader_list.push_back(std::move(*shader));
	}

	gl3::program program;
	bool linked = program.link( shader_list );
	if (!linked)
		return -1;

	return add_resource( files.front().path, std::move(program) );
}

namespace {
//! Storage required for one OpenGL RGBA8 image
size_t rgba8_size( size_t width, size_t height )
{
	constexpr size_t bytes_per_pixel = 4;
	return width * height * bytes_per_pixel;
}

//! Does the decoded image hold as many pixels as its dimensions claim?
bool has_enough_pixels( png::image const& img )
{
	return img.data.size() >= rgba8_size( img.width, img.height );
}
} // namespace

size_t texture_manager::create_texture( string_view name )
{
	io::input_file_stream ts{name};

	auto img = png::read(ts);
	if (!img) {
		journal.error( "texture", "cannot read image: " + std::string(name) );
		return -1;
	}

	if (!has_enough_pixels(*img)) {
		journal.error( "texture", "image is smaller than its own dimensions" );
		return -1;
	}

	return add_resource( name, texture{ img->data, img->width, img->height} );
}

// TODO: TEMPORARY
size_t texture_manager::create_texture_array( array_view<string_view> names )
{
	if (names.empty())
		return -1;

	png::image img;
	bool first = true;
	for (auto name : names) {
		io::input_file_stream ts{name};

		auto tmp = png::read(ts);
		if (!tmp) {
			journal.error( "texture", "cannot read image: " + std::string(name) );
			return -1;
		}

		if (first) {
			img.width  = tmp->width;
			img.height = tmp->height;
			first = false;
		} else if (tmp->width != img.width || tmp->height != img.height) {
			journal.error( "texture", "array layers differ in size" );
			return -1;
		}

		if (!has_enough_pixels(*tmp)) {
			journal.error( "texture", "image is smaller than its own dimensions" );
			return -1;
		}

		img.data.insert( img.data.end(), tmp->data.begin(), tmp->data.end() );
	}

	return add_resource( names[0], texture{ img.data, names.size(), img.width, img.height} );
}
} // namespace aw::gl3
