#include <aw/meta/find_index.h>

#include <type_traits>
namespace aw {
static_assert( find_index<std::is_same<int,_1>, void,void,void,int,void> == 3 );
} // namespace aw

#include <iostream>
int main()
{
	std::cout << aw::find_index<std::is_same<aw::_1,int>, void,void,void,int,void>;
}
