#include <aw/test/test.h>
#include <aw/utility/helpers/static_helpers.h>

TestFile( "static_object" );

namespace aw {
namespace {
/* explicit instantiation */
bool flag1 = false;
bool flag2 = false;
template<bool* flag>
struct turn_flag {
	turn_flag() { *flag = true; }

	void do_nothing() const {}
};
} // namespace

template struct static_object<turn_flag<&flag1>>;

Test(explicit_instantiation)
{
	TestEqual( flag1, true );
}

Test(implicit_instantiation)
{
	static_object<turn_flag<&flag2>>::instance().do_nothing();

	TestEqual( flag2, true );
}

/* call_on_init */
namespace {
bool flag3 = false;
auto lambda = [] {
	flag3 = true;
};
} // namespace

template struct call_on_init<+lambda>;

Test(call_on_init)
{
	TestEqual( flag3, true );
}

} // namespace aw
