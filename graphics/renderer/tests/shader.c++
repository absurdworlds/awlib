/*
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
// awgl's headers first: see the note in gl_context.c++.
#include <aw/gl/api/gl_33.h>
#include <aw/gl/api/gl_46.h>
#include <aw/graphics/gl/shader.h>

#include "gl_context.h"
#include <aw/test/test.h>

TestFile( "graphics::gl3::shader" );

namespace aw::gl3 {
namespace {
constexpr char valid_vertex_shader[] =
	"#version 330\n"
	"void main() { gl_Position = vec4(0.0, 0.0, 0.0, 1.0); }\n";

constexpr char invalid_vertex_shader[] =
	"#version 330\n"
	"this is not glsl\n";

/*
 * Without a context the entry points are null, so a test that kept going
 * would segfault instead of reporting. TestAssert does not end a test and the
 * framework cannot skip, so every test has to bail out by hand.
 */
bool have_context()
{
	auto& ctx = test::shared_gl_context();
	if (!ctx.ok())
		TestFail( ctx.error() );
	return ctx.ok();
}
} // namespace

Test(gl_context_is_available) {
	Checks {
		TestAssert( have_context() );
	}
}

Test(all_entry_points_loaded) {
	if (!have_context()) return;

	Checks {
		TestEqual( test::shared_gl_context().missing_entry_points(), 0 );
	}
}

Test(compiles_valid_glsl) {
	if (!have_context()) return;

	shader shd{gl::shader_type::vertex, valid_vertex_shader};

	Checks {
		TestAssert( shd.is_compiled() );
		TestEqual( shd.type() == gl::shader_type::vertex, true );
	}
}

Test(rejects_invalid_glsl) {
	if (!have_context()) return;

	shader shd{gl::shader_type::vertex, invalid_vertex_shader};

	Checks {
		TestAssert( !shd.is_compiled() );
	}
}

Test(move_leaves_no_double_delete) {
	if (!have_context()) return;

	Checks {
		{
			shader original{gl::shader_type::fragment,
				"#version 330\nvoid main() { }\n"};
			TestAssert( original.is_compiled() );

			shader moved{std::move(original)};
			TestAssert( moved.is_compiled() );
		} // both destructors run here

		TestEqual( ::gl::get_error(), GLenum(GL_NO_ERROR) );
	}
}
} // namespace aw::gl3
