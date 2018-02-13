/*
 * Copyright (C) 2017  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_graphics_gl3_render_context_h
#define aw_graphics_gl3_render_context_h
#include <vector>
#include <aw/graphics/gl/program.h>
#include <aw/graphics/gl/model.h>
#include <aw/graphics/gl/camera.h>
#include <aw/graphics/gl/material_manager.h>

namespace aw {
namespace gl3 {
struct render_context {
	program*  active_program;
	material* active_material;
	camera*   active_camera;
	mat4      camera_position;

	void use_program( program& prg )
	{
		gl::use_program( program_handle{prg} );
		active_program  = &prg;
		active_material = nullptr;
	}

	void use_material( material& mtl )
	{
		// assert( active_material == mtl.program )
		active_material = &mtl;
	}
};
} // namespace gl3
} // namespace aw
#endif//aw_graphics_gl3_render_context_h
