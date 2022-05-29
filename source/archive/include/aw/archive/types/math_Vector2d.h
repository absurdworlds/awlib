/*
 * Copyright (C) 2016  Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_archive_math_Vector2d
#define aw_archive_math_Vector2d
#include <aw/math/Vector2d.h>
#include <aw/archive/InputArchive.h>
#include <aw/archive/OutputArchive.h>
namespace aw {
namespace arc {
inline namespace v2 {
template<typename T>
void save(OutputArchive& arc, Vector2d<T> const& vec2)
{
	arc("x", vec2.x());
	arc("y", vec2.y());
}

template<typename T>
void load(InputArchive& arc, Vector2d<T>& vec2)
{
	arc("x", vec2.x());
	arc("y", vec2.y());
}
} // inline namespace v2
} // namespace arc
} // namespace aw
#endif//aw_archive_math_Vector2d
