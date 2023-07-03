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

struct A {};
struct B : A {};
struct C : B {};
struct D : C {};
struct U {};

template<typename T1, typename T2>
using not_related = std::negation<std::disjunction<std::is_base_of<T1, T2>, std::is_base_of<T2, T1>>>;

static_assert(
	is_same_v<
		find_type< not_related<A, _1>, B, C, D, B, U, D >,
		U
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
