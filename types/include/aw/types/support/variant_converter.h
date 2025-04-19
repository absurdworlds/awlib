#ifndef aw_types_variant_converter_h
#define aw_types_variant_converter_h

#include <utility>
#include <variant>

namespace aw {

//! Variant converter, helpts to convert variants of compatible but distinct types
template<typename Variant>
class variant_converter {
	Variant&& tmp;

public:
	template<typename U>
	variant_converter(U&& tmp)
		: tmp{std::forward<U>(tmp)}
	{
	}

	template<typename... Us>
	operator std::variant<Us...>()
	{
		return std::visit([](auto&& arg) {
			return std::variant<Us...>(std::forward<decltype(arg)>(arg));
		}, std::forward<Variant>(tmp));
	}
};

template<typename... Ts>
variant_converter(std::variant<Ts...>&&) -> variant_converter<std::variant<Ts...>>;

template<typename... Ts>
variant_converter(std::variant<Ts...>&) -> variant_converter<std::variant<Ts...>&>;

} // namespace aw
#endif // aw_types_variant_converter_h
