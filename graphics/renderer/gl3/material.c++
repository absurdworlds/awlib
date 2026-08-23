/*
 * Copyright (C) 2017  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <aw/graphics/gl/material_manager.h>
#include <aw/ranges/ipairs.h>
#include <aw/gl/wrapper/texture_func.h>

namespace aw::gl3 {
material::material( program_ref prg, char const* transform )
	: prg{prg}
{
	if (this->prg.is_valid())
		model_to_camera = this->prg.get().uniform( transform );
}

void material::add_texture( const char* name, texture_ref r )
{
	gl3::program& program = prg;
	textures.emplace_back( program.uniform(name), r );
}

void material::bind_parameters( )
{
	gl3::program& program = prg;
	auto visitor = [&] (uniform_location loc) {
		return [&] (auto v) {
			program[loc] = v;
		};
	};
	for (auto&& [i, p] : ipairs(parameters))
		std::visit( visitor(p.first), p.second );
	
}
void material::bind_textures( )
{
	gl3::program& program = prg;
	// gl::use_program( program_handle{ program } );
	for (auto&& [i, t] : ipairs(textures)) {
		gl::active_texture(GL_TEXTURE0 + i);
		texture& tex = t.second;
		gl::bind_texture(tex.type(), texture_handle{tex});
		program[t.first] = GLint(i);
	}
	// gl::use_program( gl::no_program );
}
} // namespace aw::gl3
