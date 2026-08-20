/*
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */

/*
 * GL decides which glUniform* a uniform will accept from the type it was
 * declared with, and rejects the rest. These check what a driver actually
 * does with the calls uniform_proxy makes, rather than which one it picked.
 */
// awgl's headers first: see the note in gl_context.c++.
#include <aw/gl/api/gl_33.h>
#include <aw/gl/api/gl_46.h>
#include <aw/graphics/gl/program.h>
#include <aw/gl/wrapper/gl_func.h>
#include <aw/gl/wrapper/shader_func.h>
#include <aw/types/optional.h>

#include "gl_context.h"
#include <aw/test/test.h>

#include <vector>

TestFile( "graphics::gl3::uniform" );

namespace aw::gl3 {
namespace {
constexpr char vertex_shader[] =
	"#version 330\n"
	"void main() { gl_Position = vec4(0.0, 0.0, 0.0, 1.0); }\n";

/*
 * Both uniforms have to be read for the linker to keep them; an unused one
 * has no location and nothing below would be testing anything.
 */
constexpr char fragment_shader[] =
	"#version 330\n"
	"uniform uint count;\n"
	"uniform sampler2D albedo;\n"
	"out vec4 colour;\n"
	"void main() { colour = texture(albedo, vec2(0.0)) * float(count); }\n";

// see the note in shader.c++: every test has to bail out by hand
bool have_context()
{
	auto& ctx = test::shared_gl_context();
	if (!ctx.ok())
		TestFail( ctx.error() );
	return ctx.ok();
}

optional<program> current_program()
{
	std::vector<shader> stages;
	stages.emplace_back( gl::shader_type::vertex,   vertex_shader );
	stages.emplace_back( gl::shader_type::fragment, fragment_shader );

	program prg;
	if (!prg.link( stages ))
		return nullopt;

	gl::use_program( program_handle{prg} );
	return {std::move(prg)};
}
} // namespace

Test(uint_uniform_keeps_a_value_above_int_max) {
	if (!have_context()) return;

	auto prg = current_program();

	Preconditions {
		TestAssert( prg.has_value() );
	}
	if (!prg) return;

	auto loc = prg->uniform( "count" );

	Preconditions {
		TestAssert( loc != gl::invalid_uniform );
	}

	::gl::get_error(); // discard anything left over from linking

	// no signed path could carry this value
	constexpr GLuint big = 4000000000u;
	(*prg)[loc] = big;
	auto err = ::gl::get_error();

	GLuint read = 0;
	gl::get_uniform( program_handle{*prg}, loc, &read );

	Checks {
		TestEqual( err, GLenum(GL_NO_ERROR) );
		TestEqual( read, big );
	}
}

Test(sampler_uniform_refuses_an_unsigned_value) {
	if (!have_context()) return;

	auto prg = current_program();

	Preconditions {
		TestAssert( prg.has_value() );
	}
	if (!prg) return;

	auto loc = prg->uniform( "albedo" );

	Preconditions {
		TestAssert( loc != gl::invalid_uniform );
	}

	::gl::get_error();

	// what bind_textures does
	(*prg)[loc] = GLint(1);
	auto as_signed = ::gl::get_error();

	// what it would do if a texture unit were passed as unsigned
	(*prg)[loc] = GLuint(2u);
	auto as_unsigned = ::gl::get_error();

	GLint read = 0;
	gl::get_uniform( underlying(program_handle{*prg}), underlying(loc), &read );

	Checks {
		TestEqual( as_signed,   GLenum(GL_NO_ERROR) );
		TestEqual( as_unsigned, GLenum(GL_INVALID_OPERATION) );

		// the rejected call didn't change the value
		TestEqual( read, GLint(1) );
	}
}
} // namespace aw::gl3
