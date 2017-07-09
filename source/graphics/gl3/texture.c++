/*
 * Copyright (C) 2016  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <aw/graphics/gl/texture.h>
#include <aw/graphics/gl/awgl/texture_func.h>

namespace aw::gl3 {
texture::texture( array_view<std::byte> data, size_t width, size_t height )
{
	gl::gen_textures(1, &handle);
	gl::bind_texture(GL_TEXTURE_2D, handle);
	gl::tex_image_2d(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, data.data()
	);
	gl::tex_parameter_i(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
	gl::tex_parameter_i(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
	gl::bind_texture(GL_TEXTURE_2D, gl::no_texture);
}

void texture::cleanup()
{
	gl::delete_textures(1, &handle);
}

texture::operator texture_handle()
{
	return handle;
}

} // namespace aw::gl3
