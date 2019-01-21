#include <aw/utility/hash.h>
#include <aw/utility/test.h>

TestFile( "hash_combine" );

namespace aw {
Test(hash_combine)
{
	constexpr auto expect = 0x62a4a365c3e8bce7ull;
	constexpr auto h1 = 0ull;
	constexpr auto h2 = 0b100000000ull;


	Checks {
		TestEqual(hash_combine(h1,h2),expect);
	};
}
} // namespace aw
