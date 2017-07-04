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
enum class shader_handle : GLuint {};

namespace gl {
enum class shader_type : GLenum {
	fragment = 0x8B30,
	vertex   = 0x8B31,
	geometry = 0x8DD9,
};


constexpr string_view enum_string( shader_type type )
{
	using namespace std::string_view_literals;
	switch( type ) {
	case shader_type::fragment: return "fragment"sv;
	case shader_type::vertex:   return "vertex"sv;
	case shader_type::geometry: return "geometry"sv;
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

	shader(gl::shader_type type);
	shader(gl::shader_type type, string_view source)
		: shader{type}
	{
		compile(source);
	}

	~shader() { cleanup(); }

	shader(shader const&) = delete;
	// TODO: currently makes old one invalid, bad
	shader(shader&& other)
		: _shader{other._shader}
	{
		other._shader = 0;
	}


	void swap(shader& other)
	{
		std::swap(_shader, other._shader);
	}

	shader& operator=(shader&& other)
	{
		cleanup();
		swap(other);
		return *this;
	}

	bool compile(string_view code);

	gl::shader_type type() const;
	bool is_compiled() const;
	shader_handle handle() const;

private:

	void cleanup();

	GLuint _shader = 0;
};

} // namespace gl3
} // namespace aw
#endif//aw_graphics_gl3_shader_h
