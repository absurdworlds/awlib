/*
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <aw/gl/api/gl_33.h>
#include <aw/graphics/gl/material_manager.h>

#include <aw/test/test.h>

#include <vector>

TestFile( "graphics::gl3 program" );

namespace aw::gl3 {
namespace {
GLuint next_handle = 1;
size_t attached    = 0;

GLuint fake_create_shader(GLenum) { return next_handle++; }
void fake_delete_shader(GLuint) {}
void fake_shader_source(GLuint, GLsizei, GLchar const* const*, GLint const*) {}
void fake_compile_shader(GLuint) {}

void fake_get_shader_iv(GLuint, GLenum pname, GLint* params)
{
	switch (pname) {
	case GL_COMPILE_STATUS:  *params = GL_TRUE; break;
	case GL_INFO_LOG_LENGTH: *params = 1; break;
	case GL_SHADER_TYPE:     *params = GL_VERTEX_SHADER; break;
	default:                 *params = 0; break;
	}
}

void fake_get_shader_info_log(GLuint, GLsizei, GLsizei*, GLchar* log) { log[0] = '\0'; }

GLuint fake_create_program() { return next_handle++; }
void fake_delete_program(GLuint) {}
void fake_attach_shader(GLuint, GLuint) { ++attached; }
void fake_detach_shader(GLuint, GLuint) {}
void fake_link_program(GLuint) {}

void fake_get_program_iv(GLuint, GLenum pname, GLint* params)
{
	switch (pname) {
	case GL_LINK_STATUS:     *params = GL_TRUE; break;
	case GL_INFO_LOG_LENGTH: *params = 1; break;
	default:                 *params = 0; break;
	}
}

void fake_get_program_info_log(GLuint, GLsizei, GLsizei*, GLchar* log) { log[0] = '\0'; }

void install_fake_gl()
{
	::gl::create_shader         = fake_create_shader;
	::gl::delete_shader         = fake_delete_shader;
	::gl::shader_source         = fake_shader_source;
	::gl::compile_shader        = fake_compile_shader;
	::gl::get_shader_iv         = fake_get_shader_iv;
	::gl::get_shader_info_log   = fake_get_shader_info_log;
	::gl::create_program        = fake_create_program;
	::gl::delete_program        = fake_delete_program;
	::gl::attach_shader         = fake_attach_shader;
	::gl::detach_shader         = fake_detach_shader;
	::gl::link_program          = fake_link_program;
	::gl::get_program_iv        = fake_get_program_iv;
	::gl::get_program_info_log  = fake_get_program_info_log;

	next_handle = 1;
	attached    = 0;
}

constexpr auto rejected = size_t(-1);
} // namespace

Test(program_does_not_link_without_shaders) {
	install_fake_gl();

	program prg;
	std::vector<shader> none;

	Checks {
		TestAssert( !prg.link( none ) );
		TestEqual( attached, size_t(0) );
	}
}

Test(program_manager_rejects_a_nonexistant_shader) {
	install_fake_gl();

	shader_source sources[] = {
		{ gl::shader_type::vertex,   "data/passthrough.vsh" },
		{ gl::shader_type::fragment, "data/does_not_exist.fsh" },
	};

	program_manager pman;

	Checks {
		// the vertex shader alone would link, and draw nothing
		TestEqual( pman.create_program( sources ), rejected );
		TestEqual( pman.count(), size_t(0) );
	}
}

Test(program_manager_accepts_a_complete_set) {
	install_fake_gl();

	shader_source sources[] = {
		{ gl::shader_type::vertex,   "data/passthrough.vsh" },
		{ gl::shader_type::fragment, "data/passthrough.fsh" },
	};

	program_manager pman;

	Checks {
		TestAssert( pman.create_program( sources ) != rejected );
		TestEqual( attached, size_t(2) );
	}
}
} // namespace aw::gl3
