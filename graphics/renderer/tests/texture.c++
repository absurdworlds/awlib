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

TestFile( "graphics::gl3 texture" );

namespace aw::gl3 {
namespace {
struct upload {
	GLsizei width  = 0;
	GLsizei height = 0;
	GLsizei depth  = 0;
	bool    has_data = false;
};

std::vector<upload> uploads;
GLuint next_handle = 1;

void fake_gen_textures(GLsizei n, GLuint* textures)
{
	for (GLsizei i = 0; i < n; ++i)
		textures[i] = next_handle++;
}

void fake_delete_textures(GLsizei, const GLuint*) {}
void fake_bind_texture(GLenum, GLuint) {}
void fake_tex_parameter_i(GLenum, GLenum, GLint) {}

void fake_tex_image_2d(GLenum, GLint, GLint, GLsizei width, GLsizei height,
                       GLint, GLenum, GLenum, const void* pixels)
{
	uploads.push_back({width, height, 1, pixels != nullptr});
}

void fake_tex_image_3d(GLenum, GLint, GLint, GLsizei width, GLsizei height,
                       GLsizei depth, GLint, GLenum, GLenum, const void* pixels)
{
	uploads.push_back({width, height, depth, pixels != nullptr});
}

void install_fake_gl()
{
	::gl::gen_textures    = fake_gen_textures;
	::gl::delete_textures = fake_delete_textures;
	::gl::bind_texture    = fake_bind_texture;
	::gl::tex_parameter_i = fake_tex_parameter_i;
	::gl::tex_image_2d    = fake_tex_image_2d;
	::gl::tex_image_3d    = fake_tex_image_3d;

	uploads.clear();
	next_handle = 1;
}

constexpr auto rejected = size_t(-1);

size_t make_array(std::vector<string_view> names)
{
	texture_manager tman;
	return tman.create_texture_array(names);
}
} // namespace

Test(texture_array_rejects_mismatched_layers) {
	install_fake_gl();

	Checks {
		// larger layer last: GL would have been told to read past the end
		TestEqual( make_array({"data/odd_size.png", "data/layer0.png"}), rejected );

		// smaller layer last: silently drops the tail of the data instead
		TestEqual( make_array({"data/layer0.png", "data/odd_size.png"}), rejected );

		// nothing reached GL in either case
		TestEqual( uploads.size(), size_t(0) );
	}
}

Test(texture_array_rejects_empty_list) {
	install_fake_gl();

	Checks {
		TestEqual( make_array({}), rejected );
		TestEqual( uploads.size(), size_t(0) );
	}
}

Test(texture_array_rejects_missing_file) {
	install_fake_gl();

	Checks {
		TestEqual( make_array({"data/does_not_exist.png"}), rejected );
		TestEqual( make_array({"data/layer0.png", "data/does_not_exist.png"}), rejected );
		TestEqual( uploads.size(), size_t(0) );
	}
}

Test(texture_array_uploads_layer_dimensions) {
	install_fake_gl();

	auto id = make_array({"data/layer0.png", "data/layer1.png"});

	Checks {
		TestAssert( id != rejected );
		TestEqual( uploads.size(), size_t(1) );

		if (uploads.size() == 1) {
			TestEqual( uploads[0].width,  GLsizei(4) );
			TestEqual( uploads[0].height, GLsizei(4) );
			TestEqual( uploads[0].depth,  GLsizei(2) );
			TestAssert( uploads[0].has_data );
		}
	}
}

Test(texture_uploads_image_dimensions) {
	install_fake_gl();

	texture_manager tman;
	auto id = tman.create_texture("data/layer0.png");

	Checks {
		TestAssert( id != rejected );
		TestEqual( uploads.size(), size_t(1) );

		if (uploads.size() == 1) {
			TestEqual( uploads[0].width,  GLsizei(4) );
			TestEqual( uploads[0].height, GLsizei(4) );
			TestAssert( uploads[0].has_data );
		}
	}
}
} // namespace aw::gl3
