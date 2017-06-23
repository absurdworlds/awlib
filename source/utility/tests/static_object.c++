#include <aw/utility/test.h>
#include <aw/utility/static_object.h>

TestFile( "static_object" );

namespace aw {
bool flag = false;
struct turn_flag {
	turn_flag() { flag = true; }
};

template struct static_object<turn_flag>;

Test(force_init)
{
	TestEqual( flag, true );
}
} // namespace aw
