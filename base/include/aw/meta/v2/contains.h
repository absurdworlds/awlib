#ifndef aw_meta_contains_h
#define aw_meta_contains_h
#include <type_traits>
namespace aw::meta {
inline namespace v2 {

template<typename T, typename C>
struct contains;

template<typename T, template<typename...> typename C, typename...Ts>
struct contains<T, C<Ts...>> : std::bool_constant< ( std::is_same_v<T,Ts> || ... ) > {};

template<typename T, typename C>
constexpr bool contains_v = contains<T,C>::value;

} // namespace v2
} // namespace aw::meta
#endif // aw_meta_contains_h
