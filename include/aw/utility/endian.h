/*
 * Copyright (C) 2016  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_utility_endian_h
#define aw_utility_endian_h
#include <aw/types/types.h>
#include <array>
namespace aw {
constexpr u32 read_le32(u8 a, u8 b, u8 c, u8 d)
{
	return u32{a} | u32{b} << 8 | u32{c} << 16 | u32{d} << 24;
}

constexpr u32 read_le32(const u8 (&c)[4])
{
	return u32{c[0]} | u32{c[1]} << 8 | u32{c[2]} << 16 | u32{c[3]} << 24;
}

constexpr std::array<u8,4> store_le32(u32 tag)
{
	return {u8(tag), u8(tag >> 8), u8(tag >> 16), u8(tag >> 24)};
}

constexpr u32 read_be32(u8 a, u8 b, u8 c, u8 d)
{
	return u32{d} | u32{c} << 8 | u32{b} << 16 | u32{a} << 24;
}

constexpr u32 read_be32(const u8 (&c)[4])
{
	return u32{c[3]} | u32{c[2]} << 8 | u32{c[1]} << 16 | u32{c[0]} << 24;
}

constexpr std::array<u8,4> store_be32(u32 tag)
{
	return {u8(tag >> 24), u8(tag >> 16), u8(tag >> 8), u8(tag)};
}


constexpr u32 operator""_le32(const char* str, size_t size)
{
	return read_le32(str[0], str[1], str[2], str[3]);
}

constexpr u32 operator""_be32(const char* str, size_t size)
{
	return read_be32(str[0], str[1], str[2], str[3]);
}
} // namespace aw
#endif//aw_utility_endian_h
