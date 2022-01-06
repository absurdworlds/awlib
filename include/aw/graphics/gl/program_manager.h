/*
 * Copyright (C) 2016  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_graphics_gl3_program_manager_h
#define aw_graphics_gl3_program_manager_h
#include <vector>
#include <aw/graphics/gl/program.h>
#include <aw/graphics/gl/resource_manager.h>
//#include <aw/types/containers/flat_map.h>
#include <aw/types/string_view.h>
namespace aw {
namespace gl3 {

struct program_manager : resource_manager<program> {
	// TODO: create from shader list, not this
	size_t create_program( string_view vsh, string_view fsh );
};
using program_ref = program_manager::reference;

} // namespace gl3
} // namespace aw
#endif//aw_graphics_gl3_program_manager_h
