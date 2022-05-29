/*
 * Copyright (C) 2016  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_graphics_gl3_texture_h
#define aw_graphics_gl3_texture_h
#include <aw/graphics/gl/awgl/texture_enum.h>
#include <aw/types/array_view.h>
#include <aw/graphics/export.h>
namespace aw {
namespace gl3 {
using gl::texture_handle;

struct AW_GRAPHICS_EXP texture {
	// TODO: various formats
	texture( array_view<std::byte> data, size_t height, size_t width );

	// TODO: this is a placeholder until I implement textures properly
	texture( array_view<std::byte> data, size_t count, size_t width, size_t height );

	~texture() { cleanup(); }

	texture(texture&& other)
		: handle{other.handle}, _type{other._type}
	{
		other.handle = gl::no_texture;
	}

	texture& operator=(texture&& other)
	{
		cleanup();
		handle = other.handle;
		other.handle = gl::no_texture;
		_type = other._type;
		return *this;
	}

	explicit operator texture_handle();

	GLenum type() const { return _type; }

private:
	void cleanup();
	texture_handle handle;
	GLenum _type;
};
} // namespace gl3
} // namespace aw
#endif//aw_graphics_gl3_texture_h
