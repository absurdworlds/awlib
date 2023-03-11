#include <aw/test/test.h>
#include <aw/utility/type_name.h>

TestFile( "type_name" );

using namespace std::string_view_literals;

namespace aw {
// doesn't give details
//static_assert( type_name<void>::value == "void"sv );

Test(type_name)
{
	struct empty {

	};

	auto s = compiler_string<void>();

	TestEqual( type_name<void>::value, "void"sv );
	TestEqual( type_name<int>::value, "int"sv );
	TestEqual( type_name<empty>::value, "empty"sv );
}

} // namespace aw
