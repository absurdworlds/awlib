#ifndef aw_meta_is_same_h
#define aw_meta_is_same_h

#include <type_traits>

namespace aw {

using std::is_same;
using std::is_same_v;

// TODO: investigate pitfalls of doing it this way
template<typename T, typename...Ts>
constexpr bool is_one_of_v = (is_same_v<T, Ts> || ... );

template<typename T, typename...Ts>
struct is_one_of {
	static constexpr bool value = is_one_of_v<T, Ts...>;
};

} // namespace aw

#endif // aw_meta_is_same_h
