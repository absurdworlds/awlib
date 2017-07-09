/*
 * Copyright (C) 2016  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_graphics_gl3_material_manager_h
#define aw_graphics_gl3_material_manager_h
#include <variant>
#include <utility>
#include <aw/graphics/gl/program.h>
#include <aw/graphics/gl/texture.h>
#include <aw/graphics/gl/resource_manager.h>
namespace aw {
namespace gl3 {
struct program_manager : resource_manager<program> {
	// TODO: create from shader list, not this
	size_t create_program( string_view vsh, string_view fsh );
};
using program_ref = program_manager::reference;


struct texture_manager : resource_manager<texture> {
	size_t create_texture( string_view name );
};
using texture_ref = texture_manager::reference;

struct material {
	program_ref prg;
	uniform_location model_to_camera = ((program&)prg).uniform("transform");

	void bind_parameters();
	void bind_textures();

	void add_texture( const char* name, texture_ref r );

	using parameter = std::pair<uniform_location, std::variant<int, float>>;
	std::vector<parameter> parameters;
	using tex_param = std::pair<uniform_location, texture_ref>;
	std::vector<tex_param> textures;
};

struct material_manager : resource_manager<material> {
};
using material_ref = material_manager::reference;
} // namespace gl3
} // namespace aw
#endif//aw_graphics_gl3_material_manager_h
