/*
 * Copyright (C) 2016  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_io_endian_h
#define aw_io_endian_h
#include <limits>
#include <aw/types/types.h>
#include <aw/utility/ranges/reverse.h>
namespace aw {
namespace io {
template<typename T>
bool read_le(input_stream& stream, T& out)
{
	u8 temp[sizeof(T)];
	if (!stream.read(temp))
		return false;

	out = T{};
	size_t shift = 0;
	for (auto byte : temp) {
		out   |= T(byte) << shift;
		shift += std::numeric_limits<u8>::digits;
	}
	return true;
}

template<typename T>
bool read_be(input_stream& stream, T& out)
{
	u8 temp[sizeof(T)];
	if (!stream.read(temp))
		return false;

	out = T{};
	size_t shift = 0;
	for (auto byte : reverse(temp)) {
		out   |= T(byte) << shift;
		shift += std::numeric_limits<u8>::digits;
	}
	return true;
}
} // namespace io
} // namespace aw
#endif//aw_io_endian_h
