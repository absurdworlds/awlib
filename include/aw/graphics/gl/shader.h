/*
 * Copyright (C) 2016  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_graphics_gl3_shader_h
#define aw_graphics_gl3_shader_h
#include <aw/graphics/gl/types.h>
#include <aw/types/string_view.h>
#include <aw/types/optional.h>
namespace aw {
namespace gl {
enum class shader_type : GLenum {
	fragment = 0x8B30,
	vertex   = 0x8B31,
	geometry = 0x8DD9,
};

constexpr string_view enum_string( shader_type type )
{
	using namespace sv_literals;
	switch( type ) {
	case shader_type::fragment: return "fragment"_s;
	case shader_type::vertex:   return "vertex"_s;
	case shader_type::geometry: return "geometry"_s;
	};
	// unreachable
}
} // namespace gl

namespace gl3 {
// TODO: interface is not finalized at this moment, need to make few decisions:
// — keep invariant or provide "is_compiled" methods?
// — what infomation to store?
// — if I make it possible to make invalid shader, do I also provide methods
// to recompile shader?
struct shader {
	// TODO: return "result<shader, status>"
	// TODO: gl3::compile and gl::4 compile?
	static optional<shader> compile(gl::shader_type type, string_view code);

	shader() = delete;
	~shader();

	shader(shader const&) = delete;
	// TODO: currently makes old one invalid, bad
	shader(shader&& other)
		: _shader{other._shader}
	{
		other._shader = 0;
	}
	//TODO: operator=

	void swap(shader& other)
	{
		std::swap(_shader, other._shader);
	}

	operator GLuint()
	{
		return _shader;
	}

private:
	shader(GLuint _shader)
		: _shader{_shader}
	{}

	//shader_type type;
	GLuint _shader = 0;
};

} // namespace gl3
} // namespace aw
#endif//aw_graphics_gl3_shader_h
