#include <aw/utility/hash.h>
#include <aw/types/string_view.h>
#include <aw/test/test.h>

TestFile( "MurmurHash3" );

namespace aw {

using namespace std::string_view_literals;

/*
 * The tests below pin the hashes to the values produced by Austin Appleby's
 * reference implementation, rather than to whatever this one happens to
 * return. MurmurHash3 is defined in terms of little-endian block reads —
 * which is why getblock32()/getblock64() go through read_le() instead of
 * loading a u32/u64 natively — so these values must hold on every target.
 */

//! Published test vectors for the 32-bit variant
Test(murmur_32_reference)
{
	struct vector {
		string_view key;
		u32 seed;
		u32 expect;
	};

	constexpr vector vectors[] = {
		{ ""sv,                                            0, 0x00000000 },
		{ ""sv,                                            1, 0x514e28b7 },
		{ ""sv,                                   0xffffffff, 0x81f16f39 },
		{ "test"sv,                                        0, 0xba6bd213 },
		{ "Hello, world!"sv,                               0, 0xc0363e43 },
		{ "The quick brown fox jumps over the lazy dog"sv, 0, 0x2e4ff723 },
	};

	Checks {
		for (auto const& v : vectors) {
			auto result = MurmurHash3_x86_32(v.key.data(), v.key.size(), v.seed);
			TestEqual(result, v.expect);
		}
	};
}

namespace {
/*
 * Prefixes of this string give every length from 0 to 17, so hashing each
 * one exercises all of the `len & 3` and `len & 15` tail branches as well
 * as the block loop.
 */
constexpr auto lengths = "0123456789abcdefgh"sv;

string_view prefix(size_t length)
{
	return lengths.substr(0, length);
}
} // namespace

//! Every tail length of the 32-bit variant
Test(murmur_32_lengths)
{
	constexpr u32 expect[] = {
		0x00000000, 0xd271c07f, 0x61ec6600, 0xec6cff8c, 0xd41994a0,
		0x19d02170, 0x7128d8fd, 0x0aef31a8, 0x56831753, 0x5081da7d,
		0x70b9a121, 0xd47c2cce, 0x79d73dc7, 0xf9f47291, 0x1a383359,
		0x862451fe, 0x36c7e0df, 0xe2ad6669,
	};

	Checks {
		for (size_t len = 0; len < std::size(expect); ++len) {
			auto key = prefix(len);
			auto result = MurmurHash3_x86_32(key.data(), key.size(), 0);
			TestEqual(result, expect[len]);
		}
	};
}

//! Every tail length of the 128-bit x86 variant
Test(murmur_32_128_lengths)
{
	constexpr seed128_32 seed { 0, 0, 0, 0 };

	constexpr seed128_32 expect[] = {
		{0x00000000, 0x00000000, 0x00000000, 0x00000000},
		{0x0ab2409e, 0xa5eb34f8, 0xa5eb34f8, 0xa5eb34f8},
		{0x0f87acb4, 0x674f3b21, 0x674f3b21, 0x674f3b21},
		{0xcd94fea5, 0x4c13d78e, 0x4c13d78e, 0x4c13d78e},
		{0xdc378fea, 0x485d3536, 0x485d3536, 0x485d3536},
		{0x35c5b3ee, 0x7b3b2116, 0x00ae1088, 0x00ae1088},
		{0xdb26dc75, 0x6ce1944b, 0xf825536a, 0xf825536a},
		{0xb708d0a1, 0x86d15c02, 0x495d053b, 0x495d053b},
		{0xaa22bf84, 0x92160402, 0x63b83c5e, 0x63b83c5e},
		{0x571b5f67, 0x75d48126, 0xd0205c30, 0x4ca675dc},
		{0x0017a61e, 0x2e528b33, 0xa5443f20, 0x57a11235},
		{0x38a2ed0f, 0x921f15e4, 0x2caa7f97, 0xa971884f},
		{0xcfaa93f9, 0xb6982a7e, 0x53412b5d, 0x04d3d08f},
		{0xc970af1d, 0xcc6d9d01, 0xdd00c683, 0xfc11eee3},
		{0x6f34d20a, 0xc0a5114d, 0xae0d83c5, 0x63f51794},
		{0x3c76c46d, 0x4d0818c0, 0xadd433da, 0xa78673fa},
		{0xfb7d4409, 0x36aed30a, 0x48ad1d9b, 0x572b3bfd},
		{0x7f1f9836, 0x516b3876, 0xac29c030, 0xf9d6f374},
	};

	Checks {
		for (size_t len = 0; len < std::size(expect); ++len) {
			auto key = prefix(len);
			auto result = MurmurHash3_x86_128(key.data(), key.size(), seed);
			TestEqual(result, expect[len]);
		}
	};
}

//! Every tail length of the 128-bit x64 variant
Test(murmur_64_128_lengths)
{
	constexpr seed128_64 seed { 0, 0 };

	constexpr seed128_64 expect[] = {
		{0x0000000000000000ull, 0x0000000000000000ull},
		{0x2ac9debed546a380ull, 0x3a8de9e53c875e09ull},
		{0x649e4eaa7fc1708eull, 0xe6945110230f2ad6ull},
		{0xce68f60d7c353bdbull, 0x00364cd5936bf18aull},
		{0x0f95757ce7f38254ull, 0xb4c67c9e6f12ab4bull},
		{0x0f04e459497f3fc1ull, 0xeccc6223a28dd613ull},
		{0x88c0a92586be0a27ull, 0x81062d6137728244ull},
		{0x13eb9fb82606f7a6ull, 0xb4ebef492fdef34eull},
		{0x8236039b7387354dull, 0xc3369387d8964920ull},
		{0x4c1e87519fe738baull, 0x72a17af899d597f1ull},
		{0x3f9652ac3effeb24ull, 0x8027a17cf2990b07ull},
		{0x4bc3eacd29d38629ull, 0x7cb2d9e797da9c92ull},
		{0x66352b8cee9e3ca7ull, 0xa9edf0b381a8fc58ull},
		{0x5eb2f8db4265931eull, 0x801ce853e61d0ab7ull},
		{0x07a4a014dd59f71aull, 0xaaf437854cd22231ull},
		{0xa62dd5f6c0bf2351ull, 0x4fccf50c7c544cf0ull},
		{0x4be06d94cf4ad1a7ull, 0x87c35b5c63a708daull},
		{0x8e32612daa45f9deull, 0x0800f4c206c372eeull},
	};

	Checks {
		for (size_t len = 0; len < std::size(expect); ++len) {
			auto key = prefix(len);
			auto result = MurmurHash3_x64_128(key.data(), key.size(), seed);
			TestEqual(result, expect[len]);
		}
	};
}

constexpr string_view input1[] = {
	"ohohohohoh"sv,
	"MurmurHash3"sv,
	"/data/models/"sv
};

constexpr string_view input2[] = {
	"astreeeng"sv,
	"MurmurHash3"sv,
	"test testing tests of tests"sv,
	"/some/random/path"sv
};

Test(murmur_32_1)
{
	constexpr u32 seed = 50819250;
	constexpr u32 expect[] = {
		1360569315, 2310193428, 4095911732
	};

	Checks {
		unsigned i = 0;
		for (auto str : input1) {
			auto result = MurmurHash3_x86_32(str.data(), str.size(), seed);
			TestEqual(result, expect[i++]);
		}
	};
}

Test(murmur_32_2)
{
	constexpr u32 seed = 0;
	constexpr u32 expect[] = {
		2605200336, 1473193682, 902246934
	};

	Checks {
		unsigned i = 0;
		for (auto str : input1) {
			auto result = MurmurHash3_x86_32(str.data(), str.size(), seed);
			TestEqual(result, expect[i++]);
		}
	};
}


Test(murmur_32_128_1)
{
	// Original murmur3 hash used 32-bit seed
	constexpr seed128_32 seed { 0xc96847a4, 0xc96847a4, 0xc96847a4, 0xc96847a4 };


	constexpr seed128_32 expect[] = {
		{359583446,  2196904450, 3153459002, 2636245123},
		{3602426735, 1544128708, 4203506069, 710541404},
		{1371638106, 607133185,  484173647,  3352470563},
		{4286810075, 2603962052, 4090107996, 318313016},
	};

	Checks {
		unsigned i = 0;
		for (auto str : input2) {
			auto result = MurmurHash3_x86_128(str.data(), str.size(), seed);
			TestEqual(result, expect[i++]);
		}
	};
}

Test(murmur_64_128_1)
{
	// Original murmur3 hash used 32-bit seed
	constexpr seed128_64 seed { 0xc96847a4, 0xc96847a4 };

	constexpr seed128_64 expect[] = {
		{0xca621b080a8cc524ull, 0xe104d28fb55bb99ull},
		{0x1109d3f799826fd9ull, 0xd35546df1860d952ull},
		{0xcebb4b0b456913a0ull, 0x61ec9a09b84d4b9full},
		{0xcc3e216bd5abcfcfull, 0xfc63f7b42d0aadf3ull},
	};

	Checks {
		unsigned i = 0;
		for (auto str : input2) {
			auto result = MurmurHash3_x64_128(str.data(), str.size(), seed);
			TestEqual(result, expect[i++]);
		}
	};
}
} // namespace aw
