#include <aw/test/test.h>
#include <aw/utility/type_name.h>

TestFile( "type_name" );

using namespace std::string_view_literals;

namespace aw {
// doesn't give details
//static_assert( type_name<void>::value == "void"sv );

Test(type_name_basic)
{
	TestEqual( type_name<void>::value, "void"sv );
	TestEqual( type_name<int>::value, "int"sv );
}

#if 0 // doesn't work reliably
namespace test {
struct empty {};
} // namespace test

Test(type_name_classes)
{
	TestEqual( type_name<test::empty>::value, "aw::test::empty"sv );
}
#endif

} // namespace aw
