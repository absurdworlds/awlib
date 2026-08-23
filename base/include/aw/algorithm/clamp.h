/*
 * Copyright (C) 2016  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_algorithm_clamp_h
#define aw_algorithm_clamp_h
#include <algorithm>
namespace aw {
/*!
 * Clamp value to range [lower; upper].
 */
template <typename T>
T clamp(T value, T lower, T upper)
{
	return std::min(upper, std::max(value, lower));
}
} // namespace aw
#endif//aw_algorithm_clamp_h
