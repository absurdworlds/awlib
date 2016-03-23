/*
 * Copyright (C) 2016  Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_archive_math_Vector4d
#define aw_archive_math_Vector4d
#include <aw/math/Vector4d.h>
#include <aw/archive/InputArchive.h>
#include <aw/archive/OutputArchive.h>
namespace aw {
namespace arc {
template<typename T>
void save(OutputArchive& arc, Vector4d<T> const& vec4)
{
	arc("x", vec4.x());
	arc("y", vec4.y());
	arc("z", vec4.z());
	arc("w", vec4.w());
}

template<typename T>
void load(InputArchive& arc, Vector4d<T>& vec4)
{
	arc("x", vec4.x());
	arc("y", vec4.y());
	arc("z", vec4.z());
	arc("w", vec4.w());
}
} // namespace arc
} // namespace aw
#endif//aw_archive_math_Vector4d
