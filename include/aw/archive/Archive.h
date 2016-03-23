/*
 * Copyright (C) 2016  Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_Archive_base
#define aw_Archive_base
#include <cassert>
#include <utility>
#include <aw/types/types.h>
#include <aw/types/traits/enable_if.h>
#include <aw/types/traits/detect.h>
#include <aw/types/traits/basic_traits.h>
namespace aw {
namespace arc {
inline namespace v2 {
namespace detail {
template <typename T> struct IsContainer : std::false_type{};
} // namespace detail

template<typename T>
constexpr auto IsContainer = detail::IsContainer<T>::value;

template<typename T>
constexpr auto IsBasic = is_arithmetic<T> || is_string<T>;

template<typename T>
constexpr auto IsCompound = !IsContainer<T> && !IsBasic<T> && !is_pointer<T>;

template<typename T>
constexpr auto IsPolymorphic = is_polymorphic<T>;

enum class ObjectKind {
	Unknown,
	Basic,
	Compound,
	List,
	Polymorphic
};

namespace detail {
template<typename T, typename = void>
struct kind_of {
	constexpr static auto value = ObjectKind::Unknown;
};

template<typename T>
struct kind_of<T*, void_if<IsPolymorphic<T>>> {
	constexpr static auto value = ObjectKind::Polymorphic;
};

template<typename T>
struct kind_of<T, void_if<IsBasic<T>>> {
	constexpr static auto value = ObjectKind::Basic;
};

template<typename T>
struct kind_of<T, void_if<IsCompound<T>>> {
	constexpr static auto value = ObjectKind::Compound;
};

template<typename T>
struct kind_of<T, void_if<arc::IsContainer<T>>> {
	constexpr static auto value = ObjectKind::List;
};
} // namespace detail

template<typename T>
constexpr ObjectKind kind_of = detail::kind_of<T>::value;
} // inline namespace v2
} // namespace arc
} // namespace aw
#endif//aw_Archive_base
