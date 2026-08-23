#include <aw/meta/is_same.h>

#include <string>

static_assert( aw::is_same_v<int, int> );
static_assert( aw::is_one_of_v<int, float, int> );
static_assert( aw::is_one_of_v<std::string_view, const char*, std::string_view, std::string> );
static_assert( !aw::is_one_of_v<int, const char*, std::string_view, std::string> );
static_assert( !aw::is_one_of_v<std::string_view, float, int> );
