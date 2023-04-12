#include <aw/meta/at_index.h>
#include <aw/types/traits/basic_traits.h>

namespace aw {
static_assert( is_same_v<at_index<0, int,float,void>, int> );
static_assert( is_same_v<at_index<1, int,float,void>, float> );
static_assert( is_same_v<at_index<2, int,float,void>, void> );
} // namespace aw

#include <iostream>
int main()
{
}
