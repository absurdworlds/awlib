#include <aw/meta/at_index.h>
#include <aw/types/traits/basic_traits.h>

namespace aw {
static_assert( is_same<at_index<1, int,float,void>, float> );
} // namespace aw

#include <iostream>
int main()
{
}
