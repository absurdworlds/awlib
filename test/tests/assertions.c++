
#include <aw/test/test.h>

TestFile( "awtest::assertions" );

namespace aw {

Test(conditions) {
	bool x = true;
	TestAssert(aw::test::_assert{}( x ) == x);
	x = false;
	TestAssert(aw::test::_assert{}( x ) == x);
	TestAssert(aw::test::equal{}( 1, 1 ));
	TestAssert(!aw::test::equal{}( 1, 2 ));
	TestAssert(!aw::test::not_equal{}( 1, 1 ));
	TestAssert(aw::test::not_equal{}( 1, 2 ));
	TestAssert(aw::test::equal_v{}( 1, 1, 1 ));
	TestAssert(!aw::test::equal_v{}( 1, 1, 1, 2 ));
}

Test(messages) {
	using namespace std::string_literals;
	aw::test::equal eq{ "1, 2" };
	eq(1, 2);
	TestAssert(eq.msg() == "expected equality: 1, 2: 1 != 2"s);
}

} // namespace aw
