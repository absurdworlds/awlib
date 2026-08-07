/*
 * Copyright (C) 2016-2026 Hedede <dev@hedede.me>
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
#include <limits>
namespace aw {
// TODO: use reinterpret_memory instead of relying on
// compiler optimisations on native platform

/*!
 * Read an integer of type T from a little-endian sequence of bytes.
 *
 * \note
 *     The result does not depend on the endianness of the host, and the
 *     source does not need to be aligned for T.
 */
template<typename T, typename Byte>
constexpr T read_le(Byte const* bytes)
{
	static_assert(sizeof(Byte) == 1, "Input must be a sequence of bytes!");

	constexpr auto bits = std::numeric_limits<u8>::digits;

	T value = T{};
	for (size_t i = 0; i < sizeof(T); ++i)
		value |= T( u8(bytes[i]) ) << (i * bits);
	return value;
}

/*!
 * Read an integer of type T from a big-endian sequence of bytes.
 * \see read_le
 */
template<typename T, typename Byte>
constexpr T read_be(Byte const* bytes)
{
	static_assert(sizeof(Byte) == 1, "Input must be a sequence of bytes!");

	constexpr auto bits = std::numeric_limits<u8>::digits;

	T value = T{};
	for (size_t i = 0; i < sizeof(T); ++i)
		value |= T( u8(bytes[i]) ) << ((sizeof(T) - 1 - i) * bits);
	return value;
}

constexpr u32 read_le32(u8 a, u8 b, u8 c, u8 d)
{
	return u32{a} | u32{b} << 8 | u32{c} << 16 | u32{d} << 24;
}

constexpr u32 read_le32(const u8 (&c)[4])
{
	return read_le<u32>(c);
}

constexpr u32 read_le64(const u8 (&c)[8])
{
	return read_le<u64>(c);
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
	return read_be<u32>(c);
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
