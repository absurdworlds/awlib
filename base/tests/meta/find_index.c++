#include <aw/meta/find_index.h>
#include <aw/types/traits/is_flat_container.h>

#include <type_traits>
#include <vector>

namespace aw {
static_assert( find_index<std::is_same<int,_1>, void,void,void,int,void> == 3 );
static_assert( find_index<std::is_integral<_1>, void,float,void,int,void> == 3 );
static_assert( find_index<is_flat_container_of<_1,int>, void,float,int,std::vector<float>,std::vector<long>,std::vector<int>> == 5 );
} // namespace aw

#ifdef AW_MANUAL_TEST
#include <iostream>
int main()
{
	std::cout << aw::find_index<std::is_same<aw::_1,int>, void,void,void,int,void>;
}
#endif
