#include <aw/meta/pp/paren.h>
#include <type_traits>
#include <tuple>
#include <utility>

static_assert( std::is_same_v< std::tuple<AW_REMOVE_PAREN( (int,int) )>, std::tuple<int,int> > );
static_assert( std::is_same_v< std::tuple<AW_REMOVE_PAREN(int)>, std::tuple<int> > );
static_assert( std::is_same_v< AW_REMOVE_PAREN( (std::pair<int,int>) ), std::pair<int,int> > );
