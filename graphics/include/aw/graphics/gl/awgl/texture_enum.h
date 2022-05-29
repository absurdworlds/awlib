/*
 * Copyright (C) 2016  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_graphics_awgl_texture_enum_h
#define aw_graphics_awgl_texture_enum_h
#include <aw/graphics/gl/api/types.h>
namespace aw {
namespace gl {
enum class texture_handle : GLuint {};
constexpr texture_handle no_texture{ 0 };
} // namespace gl
} // namespace aw
#endif//aw_graphics_awgl_texture_enum_h
