/*
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <aw/gl/api/gl_33.h>
#include <aw/graphics/gl/material_manager.h>

#include <aw/test/test.h>

#include <string>
#include <vector>

TestFile( "graphics::gl3 material" );

namespace aw::gl3 {
namespace {
std::vector<std::string> calls;
GLuint next_handle = 1;

void fake_uniform_1i(GLint location, GLint v)
{
	calls.push_back("uniform_1i(" + std::to_string(location) + ", " + std::to_string(v) + ")");
}

void fake_uniform_1ui(GLint location, GLuint v)
{
	calls.push_back("uniform_1ui(" + std::to_string(location) + ", " + std::to_string(v) + ")");
}

GLuint fake_create_program() { return next_handle++; }
void fake_delete_program(GLuint) {}
GLint fake_get_uniform_location(GLuint, const GLchar*) { return 3; }

void fake_gen_textures(GLsizei n, GLuint* textures)
{
	for (GLsizei i = 0; i < n; ++i)
		textures[i] = next_handle++;
}

void fake_delete_textures(GLsizei, const GLuint*) {}
void fake_bind_texture(GLenum, GLuint) {}
void fake_active_texture(GLenum) {}
void fake_tex_parameter_i(GLenum, GLenum, GLint) {}
void fake_tex_image_2d(GLenum, GLint, GLint, GLsizei, GLsizei, GLint, GLenum, GLenum, const void*) {}

void install_fake_gl()
{
	::gl::uniform_1i           = fake_uniform_1i;
	::gl::uniform_1ui          = fake_uniform_1ui;
	::gl::create_program       = fake_create_program;
	::gl::delete_program       = fake_delete_program;
	::gl::get_uniform_location = fake_get_uniform_location;
	::gl::gen_textures         = fake_gen_textures;
	::gl::delete_textures      = fake_delete_textures;
	::gl::bind_texture         = fake_bind_texture;
	::gl::active_texture       = fake_active_texture;
	::gl::tex_parameter_i      = fake_tex_parameter_i;
	::gl::tex_image_2d         = fake_tex_image_2d;

	calls.clear();
	next_handle = 1;
}
} // namespace

Test(material_binds_a_sampler) {
	install_fake_gl();

	program_manager pman;
	auto pref = pman[ pman.add_resource( "program", program{} ) ];

	std::byte pixel[4] = {};
	texture_manager tman;
	auto tref = tman[ tman.add_resource( "texture", texture{ pixel, 1, 1 } ) ];

	material mtl{ pref };
	mtl.add_texture( "albedo", tref );

	calls.clear();
	mtl.bind_textures();

	Checks {
		TestEqual( calls.size(), size_t(1) );

		if (calls.size() == 1)
			TestEqual( calls[0], std::string("uniform_1i(3, 0)") );
	}
}

Test(material_without_a_program_has_no_transform) {
	install_fake_gl();

	material mtl;

	Checks {
		TestAssert( !mtl.prg.is_valid() );
		TestAssert( mtl.model_to_camera == invalid_uniform );
	}
}

Test(material_finds_the_transform_uniform) {
	install_fake_gl();

	program_manager pman;
	auto pref = pman[ pman.add_resource( "program", program{} ) ];

	material mtl{ pref };

	Checks {
		TestAssert( mtl.model_to_camera != invalid_uniform );
	}
}
} // namespace aw::gl3
