/*
 * Copyright (C) 2016  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <aw/graphics/gl/program.h>
#include <aw/graphics/gl/uniform.h>
#include <aw/graphics/gl/uniform_buffer.h>
#include <aw/graphics/gl/awgl/shader_func.h>
#include <aw/graphics/gl/awgl/gl_func.h>

namespace aw::gl3 {
uniform_buffer::uniform_buffer(GLuint index, size_t size)
{
	gl::gen_buffers(1, &ubo);
	gl::bind_buffer(GL_UNIFORM_BUFFER, ubo);
	gl::buffer_data(GL_UNIFORM_BUFFER, size, nullptr, GL_STREAM_DRAW);
	gl::bind_buffer_range(GL_UNIFORM_BUFFER, index, ubo, 0, size);
	gl::bind_buffer(GL_UNIFORM_BUFFER, 0);
}

void uniform_buffer::cleanup()
{
	gl::delete_buffers(1, &ubo);
}

void uniform_buffer::set_data(size_t offset, void const* data, size_t size)
{
	gl::bind_buffer(GL_UNIFORM_BUFFER, ubo);
	gl::buffer_sub_data(GL_UNIFORM_BUFFER, offset, size, data);
	gl::bind_buffer(GL_UNIFORM_BUFFER, 0);
}

void uniform_buffer::bind(program_handle prg, uniform_block_index block)
{
	gl::uniform_block_binding(prg, block, index);
}

void uniform_buffer::bind(program& prg, uniform_block_index index)
{
	bind( program_handle{prg}, index );
}

//------------------------------------------------------------------------------
void uniform_proxy::set(GLint x)
{
	gl::uniform1i( location, x);
}
void uniform_proxy::set(GLuint x)
{
	gl::uniform1i( location, x);
}

void uniform_proxy::set(GLfloat x)
{
	gl::uniform1f( location, x);
}

void uniform_proxy::set(GLfloat x, GLfloat y)
{
	gl::uniform2f( location, x, y);
}

void uniform_proxy::set(GLfloat x, GLfloat y, GLfloat z)
{
	gl::uniform3f( location, x, y, z);
}

void uniform_proxy::set(GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	gl::uniform4f( location, x, y, z, w);
}

void uniform_proxy::set(mat4 const& m)
{
	static_assert( sizeof(vec4) == 4*sizeof(float) );
	gl::uniform_matrix4fv( location, 1, GL_TRUE, &m[0][0] );
/*
	using namespace math;
	float mt[16] = {
		get<0,0>(m), get<1,0>(m), get<2,0>(m), get<3,0>(m),
		get<0,1>(m), get<1,1>(m), get<2,1>(m), get<3,1>(m),
		get<0,2>(m), get<1,2>(m), get<2,2>(m), get<3,2>(m),
		get<0,3>(m), get<1,3>(m), get<2,3>(m), get<3,3>(m),
	};
	gl::uniform_matrix4fv( GLint(location), 1, GL_FALSE, mt );
*/
}
} // namespace aw::gl3
