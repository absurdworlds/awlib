/*
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <aw/gl/api/gl_33.h>
#include <aw/graphics/gl/model.h>

#include <aw/test/test.h>

#include <vector>

TestFile( "graphics::gl3 model" );

namespace aw::gl3 {
namespace {
struct attrib_call {
	GLuint    index;
	GLint     size;
	GLenum    type;
	GLsizei   stride;
	uintptr_t offset;
};

std::vector<attrib_call> attribs;
GLuint next_handle = 1;

void fake_gen(GLsizei n, GLuint* out)
{
	for (GLsizei i = 0; i < n; ++i)
		out[i] = next_handle++;
}

void fake_delete(GLsizei, const GLuint*) {}
void fake_bind(GLuint) {}
void fake_bind_buffer(GLenum, GLuint) {}
void fake_buffer_data(GLenum, GLsizeiptr, const void*, GLenum) {}
void fake_enable_vertex_attrib_array(GLuint) {}

void fake_vertex_attrib_pointer(GLuint index, GLint size, GLenum type,
                                GLboolean, GLsizei stride, const void* pointer)
{
	attribs.push_back({index, size, type, stride, uintptr_t(pointer)});
}

void install_fake_gl()
{
	::gl::gen_vertex_arrays           = fake_gen;
	::gl::delete_vertex_arrays        = fake_delete;
	::gl::bind_vertex_array           = fake_bind;
	::gl::gen_buffers                 = fake_gen;
	::gl::delete_buffers              = fake_delete;
	::gl::bind_buffer                 = fake_bind_buffer;
	::gl::buffer_data                 = fake_buffer_data;
	::gl::enable_vertex_attrib_array  = fake_enable_vertex_attrib_array;
	::gl::vertex_attrib_pointer       = fake_vertex_attrib_pointer;

	attribs.clear();
	next_handle = 1;
}

constexpr size_t vertex_count = 2;

//! position (3 floats), color (4 bytes), texture coordinate (2 half floats)
vertex_specification mixed_vertex(element_layout layout)
{
	vertex_specification spec;
	spec.layout = layout;
	spec.add_attribute({ +vertex_attribute_index::position,    element_type::single_float,       3 });
	spec.add_attribute({ +vertex_attribute_index::color,       element_type::unsigned_byte_norm, 4 });
	spec.add_attribute({ +vertex_attribute_index::tex_coord_1, element_type::half_float,         2 });
	return spec;
}

//! Enough bytes to back `vertex_count` vertices of the above
std::vector<std::byte> storage(64);
GLuint triangles[] = { 0, 1, 0 };

model make_model(element_layout layout)
{
	vertex_data verts{ storage, mixed_vertex(layout), vertex_count };
	mesh_data   meshes{ triangles };
	return { verts, meshes };
}
} // namespace

Test(packed_arrays_begin_after_the_whole_preceding_array) {
	install_fake_gl();

	auto m = make_model(element_layout::packed);

	Preconditions {
		TestEqual( attribs.size(), size_t(3) );
	}

	Checks {
		// each attribute is stored as its own contiguous array of
		// vertex_count elements
		TestEqual( attribs[0].offset, uintptr_t(0)  );
		TestEqual( attribs[1].offset, uintptr_t(vertex_count * 3*sizeof(f32)) );
		TestEqual( attribs[2].offset, uintptr_t(vertex_count * (3*sizeof(f32) + 4*sizeof(u8))) );

		// a packed layout has no gaps between vertices
		TestEqual( attribs[0].stride, GLsizei(0) );
	}
}

Test(interleaved_attributes_repeat_every_vertex) {
	install_fake_gl();

	auto m = make_model(element_layout::interleaved);

	Preconditions {
		TestEqual( attribs.size(), size_t(3) );
	}

	Checks {
		TestEqual( attribs[0].offset, uintptr_t(0)  );
		TestEqual( attribs[1].offset, uintptr_t(12) );
		TestEqual( attribs[2].offset, uintptr_t(16) );

		// one vertex apart
		constexpr auto vertex_size = 3*sizeof(f32) + 4*sizeof(u8) + 2*sizeof(u16);
		TestEqual( attribs[0].stride, GLsizei(vertex_size) );
		TestEqual( attribs[2].stride, GLsizei(vertex_size) );
	}
}
} // namespace aw::gl3
