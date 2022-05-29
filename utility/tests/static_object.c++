#include <aw/test/test.h>
#include <aw/utility/helpers/static_helpers.h>

TestFile( "static_object" );

namespace aw {
/* explicit instantiation */
bool flag1 = false;
template<bool* flag>
struct turn_flag {
	turn_flag() { *flag = true; }
};

template struct static_object<turn_flag<&flag1>>;

Test(explicit_instantiation)
{
	TestEqual( flag1, true );
}

/* call_on_init */
bool flag2 = false;
auto lambda = [] {
	flag2 = true;
};
template struct call_on_init<+lambda>;

Test(call_on_init)
{
	TestEqual( flag2, true );
}

} // namespace aw
