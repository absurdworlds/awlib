/*
 * Copyright (C) 2016  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <aw/graphics/gl/model.h>
#include <aw/graphics/gl/gl_ext33.h>

namespace aw::glh {
template<typename T>
void buffer_data( GLenum type, array_view<T> arr, GLenum mode )
{
	gl::buffer_data( type, arr.size() * sizeof(T), arr.data(), mode );
}
} // namespace

namespace aw::gl3 {
model::model( vert_data const& verts, mesh_data const& meshes )
{
	gl::gen_vertex_arrays(1, &vao);
	gl::bind_vertex_array(vao);

	gl::gen_buffers( 2, buf );
	gl::bind_buffer( GL_ARRAY_BUFFER, vbo() );
	glh::buffer_data( GL_ARRAY_BUFFER, verts.data, GL_STATIC_DRAW );

	gl::bind_buffer( GL_ELEMENT_ARRAY_BUFFER, ibo() );
	glh::buffer_data( GL_ELEMENT_ARRAY_BUFFER, meshes.triangles, GL_STATIC_DRAW );

	if (verts.position_offset != -1) {
		gl::enable_vertex_attrib_array( 0 );
		gl::vertex_attrib_pointer( 0, 3, GL_FLOAT, GL_FALSE, 0, verts.position_offset );
	}
	if (verts.color_offset != -1) {
		gl::enable_vertex_attrib_array( 1 );
		gl::vertex_attrib_pointer( 1, 4, GL_FLOAT, GL_FALSE, 0, verts.color_offset );
	}
	if (verts.normal_offset != -1) {
		gl::enable_vertex_attrib_array( 2 );
		gl::vertex_attrib_pointer( 2, 3, GL_FLOAT, GL_FALSE, 0, verts.normal_offset );
	}
	if (verts.texcoord_offset != -1) {
		gl::enable_vertex_attrib_array( 3 );
		gl::vertex_attrib_pointer( 3, 2, GL_FLOAT, GL_FALSE, 0, verts.texcoord_offset );
	}
	for (auto mesh : meshes.list)
		objects.push_back( mesh );

	if (objects.empty())
		objects.push_back({ meshes.triangles.size() });

	gl::bind_vertex_array( 0 );
	gl::bind_buffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
	gl::bind_buffer( GL_ARRAY_BUFFER, 0 );
}

model::~model()
{
	gl::delete_buffers( 2, buf );
	gl::delete_vertex_arrays( 1, &vao );
}
} // namespace aw::gl3
