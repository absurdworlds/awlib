/*
 * Copyright (C) 2026 Hedede <mail@hedede.me>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_type_support_variant_cast_h
#define aw_type_support_variant_cast_h
#include <utility>
#include <variant>
namespace aw {
template<typename Variant, typename... Ts>
auto variant_cast(const std::variant<Ts...>& var) -> Variant
{
	return std::visit([] (auto&& arg) {
		return Variant( std::forward<decltype(arg)>(arg) );
	}, var);
}

template<typename Variant, typename... Ts>
auto variant_cast(std::variant<Ts...>& var) -> Variant
{
	return std::visit([] (auto&& arg) {
		return Variant( std::forward<decltype(arg)>(arg) );
	}, var);
}

template<typename Variant, typename... Ts>
auto variant_cast(std::variant<Ts...>&& var) -> Variant
{
	return std::visit([] (auto&& arg) {
		return Variant( std::forward<decltype(arg)>(arg) );
	}, std::move(var));
}
} // namespace aw
#endif//aw_type_support_variant_cast_h
