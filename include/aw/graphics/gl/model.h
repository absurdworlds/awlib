/*
 * Copyright (C) 2016  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_graphics_gl3_model_h
#define aw_graphics_gl3_model_h
#include <aw/graphics/gl/api/types.h>
#include <aw/types/array_view.h>
#include <vector>
namespace aw {
namespace gl3 {

struct vert_data;
struct mesh_data;

struct model {
	model( vert_data const& verts, mesh_data const& meshes );
	model( model&& other )
		: objects{ std::move(other.objects) }
	{
		vao = other.vao;
		buf[0] = other.buf[0];
		buf[1] = other.buf[1];
		other.vao = 0;
		other.buf[0] = 0;
		other.buf[1] = 0;
	}

	model& operator=( model&& other )
	{
		objects = std::move(other.objects);
		std::swap( vao, other.vao );
		std::swap( buf, other.buf );
	}

	~model();

	struct subobject {
		size_t num_elements;
		GLint offset = 0;
	};

	GLuint vbo() { return buf[0]; }
	GLuint ibo() { return buf[1]; }

//private:
	GLuint vao;
	GLuint buf[2];

	std::vector<subobject> objects;
};

struct vert_data {
	array_view<GLfloat> data;

	size_t position_offset = -1;
	size_t color_offset    = -1;
	size_t normal_offset   = -1;
	size_t texcoord_offset = -1;

	// TODO: this is temporary setup, I want user to be able
	// fully specify format: interleaved or contiguous,
	// number of vertex attributes, and their format, etc
};

struct mesh_data {
	array_view<GLuint> triangles;
	array_view<model::subobject> list;
	// TODO: materials
};

} // namespace gl3
} // namespace aw
#endif//aw_graphics_gl3_program_h
