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
//
template <typename... Ts>
struct variant;

namespace _impl {
//-------------------------------------
// Variant functors
//-------------------------------------
// Destroys currently held value
struct variant_destroy_visitor {
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
decltype(auto) apply_dispatch(variant<Ts...> const& var, Storage* storage, Functor f);


//-------------------------------------
// Variant helpers
//-------------------------------------
/*! Builds a set of overloads F(T_i) used to choose correct type. */
template<typename T, typename...Ts>
struct choose_t : choose_t<Ts...> {
	using choose_t<Ts...>::operator();
	T operator()(T);
};

template<typename T>
struct choose_t<T> {
	T operator()(T);
};

/*! Builds a set of overloads F(Args...) used to choose correct type. */
template<typename T, typename...Ts>
struct construct_t : construct_t<T>, construct_t<Ts...> {
	using construct_t<T>::operator();
	using construct_t<Ts...>::operator();
};

template<typename T>
struct construct_t<T> {
	template<typename...Args>
	auto operator()(Args&&...) -> enable_if<is_constructible<T,Args...>, T>;
};

// Assert that Os... is subset of Ts...
template<typename...Os,typename...Ts>
static void assert_subset(variant<Os...> const&, variant<Ts...> const&)
{
	static_assert(!is_same<variant<Os...>, variant<Ts...>>,
	              "Non-template overload should've been used.");
	static_assert(is_subset<meta::list<Os...>, meta::list<Ts...>>,
	              "Other variant type must be a subset.");
}
} // namespace _impl
} // namespace aw
