/*
 * Copyright (C) 2016  absurdworlds
 * Copyright (C) 2016  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_reinterpret_type
#define aw_reinterpret_type
#include <cstring>
namespace aw {
/*!
 * Reinterpret value of type Input as a value of type Output.
 *
 * For example
 *     int x = reinterpret<int>(1.0f);
 * will reinterpret float `1.0f` into integer.
 *
 * \note
 *     Sizes of both types must match.
 * \note
 *     Good compilers optimize this to a single instruction.
 */
template<typename Output, typename Input>
Output reinterpret(Input&& in) {
	static_assert(sizeof(Output) == sizeof(Input),
	              "cannot reinterpret type: sizes don't match");
	Output out;
	std::memcpy(&out, &in, sizeof(Input));
	return out;
}
} // namespace aw
#endif//aw_reinterpret_type
