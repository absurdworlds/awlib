#ifndef awstd_type_traits_h
#define awstd_type_traits_h
namespace awstd {

template <bool, typename T = void> struct enable_if {};
template <typename T> struct enable_if<true, T> { typedef T type; };

template <typename T>
struct is_pointer { static const bool value = false; };
template <typename T>
struct is_pointer<T*> { static const bool value = true; };

} // namespace awstd
#endif//awstd_type_traits_h
