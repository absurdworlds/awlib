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
#include <aw/graphics/glsl/mat.h>

namespace aw {
namespace gl3 {
struct program;
struct material;
struct camera;
struct render_context {
	program*  active_program;
	material* active_material;
	camera*   active_camera;
	mat4      camera_position;

	void set_program( program& prg )
	{
		active_program  = &prg;
		active_material = nullptr;
	}

	void set_material( material& mtl )
	{
		// assert( active_material == mtl.program )
		active_material = &mtl;
	}
};
} // namespace gl3
} // namespace aw
#endif//aw_graphics_gl3_render_context_h
