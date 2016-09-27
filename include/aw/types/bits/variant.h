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

namespace aw {
/*! Copies constness of type A to type B*/
template<typename A, typename B>
using copy_const = conditional<is_const<A>, B const, remove_const<B>>;

//
template <typename... Ts>
struct variant;

namespace _impl {
// Assert that Os... is subset of Ts...
template<typename...Os,typename...Ts>
static void assert_subset(variant<Os...> const&, variant<Ts...> const&)
{
	static_assert(!is_same<variant<Os...>, variant<Ts...>>,
	              "Non-template overload should've been used.");
	static_assert(is_subset<meta::list<Os...>, meta::list<Ts...>>,
	              "Other variant type must be a subset.");
}

//-------------------------------------
// Variant functors
//-------------------------------------
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

// Copies value held by one variant into another
template<typename Variant>
struct variant_copy_assign_visitor {
	using return_type = void;

	template<typename T>
	void operator()(T const& value)
	{
		target.set(value);
	}

private:
	friend Variant;
	variant_copy_assign_visitor(Variant& target)
		: target{target}
	{}

	Variant& target;
};

// Moves value held by one variant into another
template<typename Variant>
struct variant_move_assign_visitor {
	using return_type = void;

	template<typename T>
	void operator()(T& value)
	{
		target.set(std::move(value));
	}

private:
	friend Variant;
	variant_move_assign_visitor(Variant& target)
		: target{target}
	{ }

	Variant& target;
};

//-------------------------------------
// Variant visitor dispatch
//-------------------------------------
template<typename...Ts, typename Storage, typename Functor>
auto apply_dispatch(variant<Ts...> const& var, Storage storage, Functor f) ->
	typename Functor::return_type;
} // namespace _impl
} // namespace aw
