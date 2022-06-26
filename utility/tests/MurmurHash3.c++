#include <aw/utility/hash.h>
#include <aw/types/string_view.h>
#include <aw/test/test.h>

TestFile( "MurmurHash3" );

namespace aw {

using namespace std::string_view_literals;
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
