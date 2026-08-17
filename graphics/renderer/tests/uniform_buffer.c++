/*
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <aw/gl/api/gl_33.h>
#include <aw/graphics/gl/uniform_buffer.h>

#include <aw/test/test.h>

#include <optional>

TestFile( "graphics::gl3 uniform buffer" );

namespace aw::gl3 {
namespace {
//! The binding point the buffer was put on
std::optional<GLuint> buffer_binding;
//! The binding point a program's block was pointed at
std::optional<GLuint> block_binding;

GLuint next_handle = 1;

void fake_gen_buffers(GLsizei n, GLuint* out)
{
	for (GLsizei i = 0; i < n; ++i)
		out[i] = next_handle++;
}

void fake_delete_buffers(GLsizei, const GLuint*) {}
void fake_bind_buffer(GLenum, GLuint) {}
void fake_buffer_data(GLenum, GLsizeiptr, const void*, GLenum) {}

void fake_bind_buffer_range(GLenum, GLuint index, GLuint, GLintptr, GLsizeiptr)
{
	buffer_binding = index;
}

void fake_uniform_block_binding(GLuint, GLuint, GLuint binding)
{
	block_binding = binding;
}

void install_fake_gl()
{
	::gl::gen_buffers           = fake_gen_buffers;
	::gl::delete_buffers        = fake_delete_buffers;
	::gl::bind_buffer           = fake_bind_buffer;
	::gl::buffer_data           = fake_buffer_data;
	::gl::bind_buffer_range     = fake_bind_buffer_range;
	::gl::uniform_block_binding = fake_uniform_block_binding;

	buffer_binding.reset();
	block_binding.reset();
	next_handle = 1;
}

constexpr GLuint binding_point = 7;
constexpr size_t block_size    = 64;
} // namespace

Test(uniform_buffer_is_bound_correctly) {
	install_fake_gl();

	uniform_buffer ubo{binding_point, block_size};
	ubo.bind( program_handle{1}, uniform_block_index{0} );

	Preconditions {
		TestAssert( buffer_binding.has_value() );
		TestAssert( block_binding.has_value() );
	}

	Checks {
		TestEqual( *buffer_binding, binding_point );
		TestEqual( *block_binding, binding_point );
	}
}

Test(uniform_buffer_keeps_binding_after_move) {
	install_fake_gl();

	uniform_buffer original{binding_point, block_size};
	uniform_buffer moved{std::move(original)};

	moved.bind( program_handle{1}, uniform_block_index{0} );

	Checks {
		TestEqual( *block_binding, binding_point );
	}
}
} // namespace aw::gl3
