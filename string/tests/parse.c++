#include <aw/string/parse.h>
#include <aw/test/test.h>

#include <aw/utility/to_string/optional.h>

TestFile( "string::parse" );

namespace aw {
Test(parse_int) {
	Checks {
		TestEqual(string::parse<int>("123"), 123);
		TestEqual(string::parse<int>("x123"), std::nullopt);
		TestEqual(string::parse<int>("x123", 100), 100);
	}
	{
		int value = 111;
		TestAssert(!string::try_parse<int>("xxx", value));
		TestEqual(value, 111);
		TestAssert(string::try_parse<int>("123", value));
		TestEqual(value, 123);
	}
}
} // namespace aw
