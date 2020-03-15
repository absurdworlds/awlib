/*
 * Copyright (C) 2014-2016 absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_types_variant_h
static_assert(false, "Do not include this file directly.");
#endif//aw_types_variant_h

#include <aw/types/strip.h>

namespace aw {
namespace _impl {
//-------------------------------------
// Variant visitor dispatch
//-------------------------------------
// Call functor on type T
template<typename T, typename R, typename Storage, typename Functor>
R apply_functor(Storage* storage, Functor func)
{
	using Type = copy_const<Storage, T>;
	return func(*reinterpret_cast<Type*>(storage));
}

template<typename Functor, typename...Ts>
using apply_result = std::common_type_t<std::invoke_result_t<Functor, Ts&>...>;

// Linear dispatch
template<typename T, typename...Ts>
struct vh_linear {
	template<class Storage, class Functor>
	static decltype(auto)
	dispatch(size_t index, Storage* storage, Functor f)
	{
		using return_type = apply_result<Functor, T, Ts...>;

		if (index == 0)
			return apply_functor<T,return_type>(storage, f);

		if constexpr (sizeof...(Ts) > 0)
			return vh_linear<Ts...>::dispatch(--index, storage, f);

		//aw_unreachable();
	}
};

// Recursive (tree) dispatch
template<size_t Start, size_t Length, typename...Ts>
struct vh_recursive {
	template<class Storage, class Functor>
	static decltype(auto)
	dispatch(size_t index, Storage* storage, Functor f)
	{
		using return_type = apply_result<Functor, Ts...>;

		if (index == Start) {
			using T = at_index<Start, Ts...>;
			return apply_functor<T, return_type>(storage, f);
		}

		if constexpr(Length > 1)
		{
			constexpr size_t Mid = Length / 2;

			if (index < Start + Mid)
				return vh_recursive<Start,Mid,Ts...>::template dispatch(index, storage, f);
			return vh_recursive<Start+Mid,Length-Mid,Ts...>::template dispatch(index, storage, f);
		}
		else
		{
			assert(index == Start);
		}
	}
};

// Jumptable dispatch
template<typename...Ts>
struct vh_jumptable {
	template<class Storage, class Functor>
	static decltype(auto)
	dispatch(size_t index, Storage* storage, Functor f)
	{
		using return_type = apply_result<Functor, Ts...>;
		using func_type   = return_type(Storage* storage, Functor f);

		static func_type* table[sizeof...(Ts)] = {
			(apply_functor<Ts, return_type, Storage, Functor>)...
		};

		return table[index](storage, f);
	}
};

template<typename...Ts, typename Storage, typename Functor>
decltype(auto) apply_dispatch(variant<Ts...> const& var, Storage* storage, Functor f)
{
	constexpr size_t treshold_binsearch = 4;
	constexpr size_t treshold_jumptable = 9;
	constexpr size_t num_types = sizeof...(Ts);

	const size_t index = size_t(var.type_index());

	if constexpr(num_types < treshold_binsearch)
		return vh_linear<Ts...>::dispatch(index, storage, f);
	if constexpr(num_types < treshold_jumptable)
		return vh_recursive<0, num_types,Ts...>::dispatch(index, storage, f);
	else
		return vh_jumptable<Ts...>::dispatch(index, storage, f);
}
} // namespace _impl
} // namespace aw
