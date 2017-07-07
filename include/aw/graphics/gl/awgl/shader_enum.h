/*
 * Copyright (C) 2016  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_graphics_awgl_shader_enum_h
#define aw_graphics_awgl_shader_enum_h
#include <aw/graphics/gl/api/types.h>
#include <aw/types/string_view.h>
namespace aw {
namespace gl {
enum class shader_handle : GLuint {};
enum class program_handle : GLuint {};
enum class uniform_location : GLint {};
enum class uniform_block_index : GLuint {};

constexpr shader_handle    no_shader{ 0 };
constexpr program_handle   no_program{ 0 };
constexpr uniform_location invalid_uniform{ -1 };

inline bool operator!(shader_handle  shader)  { return shader  == no_shader; }
inline bool operator!(program_handle program) { return program == no_program; }


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

enum class shader_param : GLenum {
	type            = 0x8B4F,
	compile_status  = 0x8B81,
	delete_status   = 0x8B80,
	info_log_length = 0x8B84,
	source_length   = 0x8B88
};

enum class program_param : GLenum {
	link_status     = 0x8B82,
	info_log_length = 0x8B84,
};
} // namespace gl
} // namespace aw
#endif//aw_graphics_awgl_shader_enum_h
