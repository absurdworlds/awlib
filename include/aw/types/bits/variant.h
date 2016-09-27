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
/*! Copies constness of type A to type B*/
template<typename A, typename B>
using copy_const = conditional<is_const<A>, B const, remove_const<B>>;

//
template <typename... Ts>
struct variant;

namespace _impl {
// Destroys currently held value
struct variant_destroy_visitor {
	using return_type = void;

	template<typename T>
	void operator()(T& data)
	{
		data.~T();
	}

private:
	variant_destroy_visitor() = default;

	template<typename... Ts>
	friend struct variant;
};

// Call functor on type T
template<typename T, typename Storage, typename Functor>
auto apply_functor(Storage* storage, Functor func) ->
	typename Functor::return_type
{
	using Type = copy_const<Storage, T>;
	return func(*reinterpret_cast<Type*>(storage));
}

template<class Variant, size_t Start, size_t Length>
struct vh_recursive {

	template<class Storage, class Functor>
	static auto dispatch(size_t index, Storage storage, Functor f) ->
		typename Functor::return_type
	{
		constexpr size_t Mid = Length / 2;
		if (index < Start + Mid)
			return vh_recursive<Variant,Start,Mid>::template dispatch(index, storage, f);
		return vh_recursive<Variant,Start+Mid,Length-Mid>::template dispatch(index, storage, f);
	}
};

template<class Variant, size_t Start>
struct vh_recursive<Variant,Start,1> {
	template<class Storage, class Functor>
	static auto
	dispatch(size_t index, Storage* storage, Functor f) ->
		typename Functor::return_type
	{
		assert(index == Start);
		using T = typename Variant::template type_at<Start>;
		return apply_functor<T>(storage, f);
	}
};

template<typename...Ts>
struct vh_jumptable {
	template<class Storage, class Functor>
	static auto
	dispatch(size_t index, Storage* storage, Functor f) ->
		typename Functor::return_type
	{
		using return_type = typename Functor::return_type;
		using func_type   = return_type(Storage* storage, Functor f);

		static func_type* table[sizeof...(Ts)] = {
			(apply_functor<Ts, Storage, Functor>)...
		};

		return table[index](storage, f);
	}
};

template<typename...Ts, typename Storage, typename Functor>
auto apply_dispatch(variant<Ts...> const& var, Storage storage, Functor f) ->
	typename Functor::return_type
{
	constexpr size_t num_types = sizeof...(Ts);
	using dispatch_type = conditional<num_types < 5,
		vh_recursive<variant<Ts...>, 0, num_types>,
		vh_jumptable<Ts...>
	>;
	size_t const index = size_t(var.type_index());
	return dispatch_type::template dispatch(index, storage, f);
}
} // namespace _impl
} // namespace aw
