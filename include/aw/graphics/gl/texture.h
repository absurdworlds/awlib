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
namespace aw {
namespace gl3 {
using gl::texture_handle;

struct texture {
	// TODO: various formats
	texture( array_view<std::byte> data, size_t height, size_t width );
	~texture() { cleanup(); }

	explicit operator texture_handle();

private:
	void cleanup();
	texture_handle handle;
};
} // namespace gl3
} // namespace aw
#endif//aw_graphics_gl3_texture_h
