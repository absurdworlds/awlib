#include <aw/config.h>
#include <aw/meta/find_type.h>

#include <type_traits>
namespace aw {
static_assert(
	is_same_v<
		meta::find_type< std::is_same<aw::_1,int>, void,void,void,int,void,float,void >,
		meta::list<int,void,float,void>
	>
);

static_assert(
	is_same_v<
		find_type< std::is_same<aw::_1,int>, void,void,void,int,void,float,void >,
		int
	>
);

} // namespace aw

#ifdef AW_MANUAL_TEST
#include <iostream>
template<typename T>
void pretty_print()
{
	std::cout << AW_FUNCTION_SIGNATURE << '\n';
}

int main()
{
	pretty_print<
		aw::meta::find_type<

		std::is_same<aw::_1,int>, void,void,void,int,void,struct hh

		>
	>();
}
#endif
