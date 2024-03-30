#include <aw/test/test.h>
#include <aw/utility/type_name.h>

TestFile( "type_name" );

using namespace std::string_view_literals;

namespace aw {
static_assert( type_name<void>::value == "void"sv );
static_assert( type_name<int>::value == "int"sv );

namespace test {
struct empty {};
} // namespace test

Test(type_name_inside_aw)
{
	TestEqual( type_name<void>::value, "void"sv );
	TestEqual( type_name<int>::value, "int"sv );
	TestEqual( type_name<test::empty>::value, "aw::test::empty"sv );
}
} // namespace aw

namespace test {
struct empty {};
} // namespace test

Test(type_name_outside_aw)
{
	TestEqual( aw::type_name<void>::value, "void"sv );
	TestEqual( aw::type_name<int>::value, "int"sv );
	TestEqual( aw::type_name<aw::test::empty>::value, "aw::test::empty"sv );
	TestEqual( aw::type_name<::test::empty>::value, "test::empty"sv );
}

class test_class {};

namespace test {
template<typename T>
std::string_view type_name2()
{
	return aw::type_name<T>::value;
}

class registrar {
public:
	template<typename T>
	void do_register()
	{
		name = type_name2<T>();
	}

	std::string_view name;
};
} // namespace test

Test(type_name_called_from_template)
{
	TestEqual( test::type_name2<test::empty>(), "test::empty"sv );
	TestEqual( test::type_name2<test_class>(), "test_class"sv );

	test::registrar r;
	r.do_register<int>();
	TestEqual( r.name, "int"sv );
	r.do_register<test_class>();
	TestEqual( r.name, "test_class"sv );
	r.do_register<test::empty>();
	TestEqual( r.name, "test::empty"sv );
}
