/*
 * Copyright (C) 2016  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <aw/graphics/gl/model.h>
#include <aw/graphics/gl/awgl/buffer_func.h>
#include <aw/graphics/gl/awgl/vertex_func.h>
#include <aw/utility/ranges/ipairs.h>

namespace aw::glh {
template<typename T>
void buffer_data( GLenum type, array_view<T> arr, GLenum mode )
{
	gl::buffer_data( type, arr.size() * sizeof(T), arr.data(), mode );
}
} // namespace


namespace aw::gl3 {
static const GLenum elem_type_value[] = {
	/**/
	GL_BYTE,
	GL_SHORT,
	GL_INT,
	GL_UNSIGNED_BYTE,
	GL_UNSIGNED_SHORT,
	GL_UNSIGNED_INT,
	/**/
	GL_BYTE,
	GL_SHORT,
	GL_INT,
	GL_UNSIGNED_BYTE,
	GL_UNSIGNED_SHORT,
	GL_UNSIGNED_INT,
	/**/
	GL_HALF_FLOAT,
	GL_FLOAT,
	GL_DOUBLE,
	/*GL_FIXED*/ 0,
	/**/
	GL_INT_2_10_10_10_REV,
	GL_UNSIGNED_INT_2_10_10_10_REV,
	GL_UNSIGNED_INT_10F_11F_11F_REV
};

static const bool elem_type_normalized[] = {
	/**/
	false, false, false, false, false, false,
	/**/
	true, true, true, true, true, true,
	/**/
	false, false, false, false,
	/**/
	false, false, false
};

GLenum to_gl(element_type type)
{
	return elem_type_value[underlying(type)];
}

bool is_normalized(element_type type)
{
	return elem_type_normalized[underlying(type)];
}

// TODO: use attribi_pointer for (non-normalized) ints
// TODO: merge these two into one... maybe
void set_attrib_interleaved( vertex_data const& verts )
{
	for (auto&& [i,type,size,offset] : verts.format.attributes) {
		gl::enable_vertex_attrib_array( i );
		gl::vertex_attrib_pointer( i,
			size,
			to_gl(type),
			is_normalized(type),
			verts.format.size,
			offset
		);
	}
}

void set_attrib_array( vertex_data const& verts )
{
	size_t offset = 0;
	for (auto&& [i,type,size,_] : verts.format.attributes) {
		gl::enable_vertex_attrib_array( i );
		gl::vertex_attrib_pointer( i,
			size,
			to_gl(type),
			is_normalized(type),
			0,
			offset
		);
		// FIXME FIXME FIXME
		// replace 4 with actual size
		offset += verts.count * size * 4;
	}
}

model::model( vertex_data const& verts, mesh_data const& meshes )
{
	gl::gen_vertex_arrays(1, &vao);
	gl::bind_vertex_array(vao);

	gl::gen_buffers( 2, buf );
	gl::bind_buffer( GL_ARRAY_BUFFER, vbo() );
	glh::buffer_data( GL_ARRAY_BUFFER, verts.data, GL_STATIC_DRAW );

	gl::bind_buffer( GL_ELEMENT_ARRAY_BUFFER, ibo() );
	glh::buffer_data( GL_ELEMENT_ARRAY_BUFFER, meshes.triangles, GL_STATIC_DRAW );

	if ( verts.format.layout == element_layout::interleaved )
		set_attrib_interleaved( verts );
	else
		set_attrib_array( verts );

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
