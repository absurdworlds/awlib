/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
//-----------------------------------------------------------------------------
// This code is based on MurmurHash3.
// MurmurHash3 was written by Austin Appleby, and is placed in the public domain.
#include <aw/math/bitmath.h>
#include <aw/types/support/reinterpret.h>
#include <aw/utility/endian.h>

#include <aw/utility/hash.h>

namespace aw {
namespace {
u8 read_byte(char const* addr)
{
	return u8(*addr);
}

u16 read_u16(char const* addr)
{
	u16 result = 0;
	result |= u16(read_byte(addr++)) << 0;
	result |= u16(read_byte(addr  )) << 8;
	return result;
}

u32 read_u32(char const* addr)
{
	u32 result = 0;
	result |= u32(read_byte(addr++)) << 0;
	result |= u32(read_byte(addr++)) << 8;
	result |= u32(read_byte(addr++)) << 16;
	result |= u32(read_byte(addr  )) << 24;
	return result;
}

u64 read_u64(char const* addr)
{
	u64 result = 0;
	result |= u64(read_byte(addr++)) << 0;
	result |= u64(read_byte(addr++)) << 8;
	result |= u64(read_byte(addr++)) << 16;
	result |= u64(read_byte(addr++)) << 24;
	result |= u64(read_byte(addr++)) << 32;
	result |= u64(read_byte(addr++)) << 40;
	result |= u64(read_byte(addr++)) << 48;
	result |= u64(read_byte(addr  )) << 56;
	return result;
}

u32 getbyte32(char const* p, int i)
{
	return u8(p[i]);
}

u64 getbyte64(char const* p, int i)
{
	return u8(p[i]);
}

u32 getblock32(char const* p, int i)
{
	p += i * sizeof(u32);
	return read_u32(p);
	// TODO: defines to switch between these
	//return reinterpret_memory<u32>(p);
	//return *reinterpret_cast<u32 const*>(p);
}

u64 getblock64(char const* p, size_t i)
{
	p += i * sizeof(u64);
	return read_u64(p);
	//return reinterpret_memory<u64>(p);
	//return *reinterpret_cast<u64 const*>(p);
}

/*!
 * Finalization mix - force all bits of a hash block to avalanche
 */
u32 fmix32 (u32 h)
{
	h ^= h >> 16;
	h *= 0x85ebca6b;
	h ^= h >> 13;
	h *= 0xc2b2ae35;
	h ^= h >> 16;

	return h;
}


u64 fmix64 (u64 k)
{
	k ^= k >> 33;
	k *= 0xff51afd7ed558ccdULL;
	k ^= k >> 33;
	k *= 0xc4ceb9fe1a85ec53ULL;
	k ^= k >> 33;
	return k;
};
} // namespace

u32 MurmurHash3_x86_32 (char const* key, size_t len, u32 seed)
{
	size_t const nblocks = len / 4;

	u32 h1 = seed;

	constexpr u32 c1 = 0xcc9e2d51;
	constexpr u32 c2 = 0x1b873593;

	constexpr u32 magic1 = 0xe6546b64;

	auto mix_1 = [] (u32 k) {
		k *= c1;
		k  = math::rotl(k,15);
		k *= c2;
		return k;
	};

	//----------
	// body

	for (size_t i = 0; i < nblocks; ++i) {
		u32 k1 = getblock32(key,i);

		h1 ^= mix_1(k1);

		h1 = math::rotl(h1,13);
		h1 = h1*5 + magic1;
	}

	//----------
	// tail

	auto tail = key + nblocks*4;

	u32 k1 = 0;

	switch (len & 3) {
	case 3: k1 ^= getbyte32(tail, 2) << 16;
	case 2: k1 ^= getbyte32(tail, 1) << 8;
	case 1: k1 ^= getbyte32(tail, 0);
	        h1 ^= mix_1(k1);
	};

	//----------
	// finalization

	h1 ^= len;
	h1 = fmix32(h1);

	return h1;
} 

seed128_32 MurmurHash3_x86_128(char const* key, size_t len, seed128_32 seed)
{
	size_t nblocks = len / 16;

	u32 h1 = seed[0];
	u32 h2 = seed[1];
	u32 h3 = seed[2];
	u32 h4 = seed[3];

	constexpr u32 c1 = 0x239b961b;
	constexpr u32 c2 = 0xab0e9789;
	constexpr u32 c3 = 0x38b34ae5;
	constexpr u32 c4 = 0xa1e38b93;

	auto mix_1 = [] (u32 k, u32 ca, u32 cb, size_t s)
	{
		k *= ca;
		k  = math::rotl(k,s);
		k *= cb;
		return k;
	};

	auto mix_2 = [] (u32 ha, u32 hb, size_t s, u32 m)
	{
		ha  = math::rotl(ha,s);
		ha += hb;
		return ha*5 + m;
	};

	//----------
	// body

	for (size_t i = 0; i < nblocks; ++i) {
		u32 k1 = getblock32(key, 4*i + 0);
		u32 k2 = getblock32(key, 4*i + 1);
		u32 k3 = getblock32(key, 4*i + 2);
		u32 k4 = getblock32(key, 4*i + 3);

		h1 ^= mix_1(k1, c1, c2, 15);
		h1  = mix_2(h1, h2, 19, 0x561ccd1b);

		h2 ^= mix_1(k2, c2, c3, 16);
		h2  = mix_2(h2, h3, 17, 0x0bcaa747);

		h3 ^= mix_1(k3, c3, c4, 17);
		h3  = mix_2(h3, h4, 15, 0x96cd1c35);

		h4 ^= mix_1(k4, c4, c1, 18);
		h4  = mix_2(h4, h1, 13, 0x32ac3b17);
	}

	//----------
	// tail

	char const* tail = key + nblocks*16;

	u32 k1 = 0;
	u32 k2 = 0;
	u32 k3 = 0;
	u32 k4 = 0;

	switch (len & 15) {
	case 15: k4 ^= getbyte32(tail, 14) << 16;
	case 14: k4 ^= getbyte32(tail, 13) << 8;
	case 13: k4 ^= getbyte32(tail, 12) << 0;
	         h4 ^= mix_1(k4, c4, c1, 18);

	case 12: k3 ^= getbyte32(tail, 11) << 24;
	case 11: k3 ^= getbyte32(tail, 10) << 16;
	case 10: k3 ^= getbyte32(tail,  9) << 8;
	case  9: k3 ^= getbyte32(tail,  8) << 0;
	         h3 ^= mix_1(k3, c3, c4, 17);

	case  8: k2 ^= getbyte32(tail,  7) << 24;
	case  7: k2 ^= getbyte32(tail,  6) << 16;
	case  6: k2 ^= getbyte32(tail,  5) << 8;
	case  5: k2 ^= getbyte32(tail,  4) << 0;
	         h2 ^= mix_1(k2, c2, c3, 16);

	case  4: k1 ^= getbyte32(tail,  3) << 24;
	case  3: k1 ^= getbyte32(tail,  2) << 16;
	case  2: k1 ^= getbyte32(tail,  1) << 8;
	case  1: k1 ^= getbyte32(tail,  0) << 0;
	         h1 ^= mix_1(k1, c1, c2, 15);
	};

	//----------
	// finalization

	h1 ^= len;
	h2 ^= len;
	h3 ^= len;
	h4 ^= len;

	h1 += h2;
	h1 += h3;
	h1 += h4;
	h2 += h1;
	h3 += h1;
	h4 += h1;

	h1 = fmix32(h1);
	h2 = fmix32(h2);
	h3 = fmix32(h3);
	h4 = fmix32(h4);

	h1 += h2;
	h1 += h3;
	h1 += h4;
	h2 += h1;
	h3 += h1;
	h4 += h1;

	return {h1, h2, h3, h4};
}

seed128_64 MurmurHash3_x64_128(char const* key, size_t len, seed128_64 seed)
{
	size_t const nblocks = len / 16;

	u64 h1 = seed[0];
	u64 h2 = seed[1];

	constexpr u64 c1 = 0x87c37b91114253d5ull;
	constexpr u64 c2 = 0x4cf5ad432745937full;

	auto mix_1 = [] (u64 k, u64 ca, u64 cb, size_t s)
	{
		k *= ca;
		k  = math::rotl(k,s);
		k *= cb;
		return k;
	};

	auto mix_2 = [] (u64 ha, u64 hb, size_t s, u64 m)
	{
		ha  = math::rotl(ha,s);
		ha += hb;
		return ha*5 + m;
	};

	//----------
	// body
	for (size_t i = 0; i < nblocks; ++i) {
		u64 k1 = getblock64(key, 2*i + 0);
		u64 k2 = getblock64(key, 2*i + 1);

		h1 ^= mix_1(k1, c1, c2, 31);
		h1  = mix_2(h1, h2, 27, 0x52dce729);

		h2 ^= mix_1(k2, c2, c1, 33);
		h2  = mix_2(h2, h1, 31, 0x38495ab5);
	}

	//----------
	// tail
	char const* tail = key + nblocks*16;

	u64 k1 = 0;
	u64 k2 = 0;

	switch (len & 15) {
	case 15: k2 ^= getbyte64(tail, 14) << 48;
	case 14: k2 ^= getbyte64(tail, 13) << 40;
	case 13: k2 ^= getbyte64(tail, 12) << 32;
	case 12: k2 ^= getbyte64(tail, 11) << 24;
	case 11: k2 ^= getbyte64(tail, 10) << 16;
	case 10: k2 ^= getbyte64(tail,  9) << 8;
	case  9: k2 ^= getbyte64(tail,  8) << 0;
		 h2 ^= mix_1(k2, c2, c1, 33);

	case  8: k1 ^= getbyte64(tail,  7) << 56;
	case  7: k1 ^= getbyte64(tail,  6) << 48;
	case  6: k1 ^= getbyte64(tail,  5) << 40;
	case  5: k1 ^= getbyte64(tail,  4) << 32;
	case  4: k1 ^= getbyte64(tail,  3) << 24;
	case  3: k1 ^= getbyte64(tail,  2) << 16;
	case  2: k1 ^= getbyte64(tail,  1) << 8;
	case  1: k1 ^= getbyte64(tail,  0) << 0;
		 h1 ^= mix_1(k1, c1, c2, 31);
	};

	//----------
	// finalization

	h1 ^= len;
	h2 ^= len;

	h1 += h2;
	h2 += h1;

	h1 = fmix64(h1);
	h2 = fmix64(h2);

	h1 += h2;
	h2 += h1;

	return {h1, h2};
}
} // namespace aw
