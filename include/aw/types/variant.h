/*
 * Copyright (C) 2014-2016 absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_types_variant_h
#define aw_types_variant_h
#include <aw/types/types.h>
#include <aw/types/strip.h>
#include <aw/types/traits/basic_traits.h>
#include <aw/meta/conditional.h>
#include <aw/meta/list_ops.h>
#include <aw/meta/find_type.h>
#include <aw/meta/index_of.h>
#include <aw/meta/at_index.h>
#include <limits>
#include <algorithm>
#include <cassert>

#include <aw/types/bits/variant.h>

namespace aw {
/*!
 * Variant type a.k.a. type-safe union.
 * Holds one type out of the list.
 */
template <typename... Ts>
struct variant {
	static_assert(sizeof...(Ts) >= 2, "variant must consist of at least 2 types");

	static constexpr size_t size  = std::max({sizeof(Ts)...});
	static constexpr size_t align = std::max({alignof(Ts)...});

	/*!
	 * Constructs empty variant.
	 */
	variant() = default;

	/*!
	 * Construct variant holding a value of type T.
	 */
	template<typename T, bool_if<is_in_pack<T,Ts...>> = true>
	variant(T const& value)
	{
		construct<T>(value);
	}

	template<typename T, bool_if<is_in_pack<T,Ts...>> = true>
	variant(T&& value)
	{
		construct<T>(std::move(value));
	}

	/*
	 * Active only if there is one variant alternative that
	 * can be constructed from (args...).
	 */
	template<typename...Args,
	         bool_if<meta::count_if<
	                 std::is_constructible<_1, Args...>, Ts...> == 1
	         > = true>
	// TODO: when C++17 is released, use std::in_place
	variant(Args&&... args)
	{
		using Predicate = std::is_constructible<_1, Args...>;
		construct<find_type<Predicate, Ts...>>(std::forward<Args>(args)...);
	}

	/*!
	 * Copy variant from another
	 */
	variant(variant const& other)
	{
		if (!other.empty())
			other.apply(copy_construct_visitor{*this});
	}

	/*!
	 * Move variant from another
	 */
	variant(variant&& other)
	{
		if (!other.empty()) {
			other.apply(move_construct_visitor{*this});
			other.reset();
		}
	}

	~variant()
	{
		if (!empty()) {
			destroy();
		}
	}

	variant& operator=(variant const& other)
	{
		copy_from(other);
		return *this;
	}

	variant& operator=(variant&& other)
	{
		assert(&other != this);
		move_from(other);
		return *this;
	}

	/*!
	 * Move variant from a subset variant type
	 */
	template<typename... Os>
	variant(variant<Os...> const& other)
	{
		_impl::assert_subset(other, *this);

		if (!other.empty())
			other.apply(copy_construct_visitor{*this});
	}

	/*!
	 * Move variant from a subset variant type
	 */
	template<typename... Os>
	variant(variant<Os...>&& other)
	{
		_impl::assert_subset(other, *this);

		if (!other.empty()) {
			other.apply(move_construct_visitor{*this});
			other.reset();
		}
	}

	template<typename... Os>
	variant& operator=(variant<Os...> const& other)
	{
		_impl::assert_subset(other, *this);

		copy_from(other);
		return *this;
	}

	template<typename... Os>
	variant& operator=(variant<Os...>&& other)
	{
		_impl::assert_subset(other, *this);

		move_from(other);
		return *this;
	}

	/*!
	 * Set variant to value v of type T.
	 * Uses assignments if variant already contains a value of type T,
	 * or destroys current value if it is of a different type.
	 */
	template<typename T>
	void set(T const& v)
	{
		if (check_type<T>()) {
			assign(v);
		} else {
			reset();
			construct<T>(v);
		}
	}

	/*!
	 * Move value v into variant.
	 */
	template<typename T>
	auto set(T&& v) -> void_if< !is_reference<T> >
	{
		if (check_type<T>()) {
			assign(std::move(v));
		} else {
			reset();
			construct<T>(std::move(v));
		}
	}

	/*!
	 * Construct value of type T from Args.
	 */
	template<typename T, typename...Args>
	void emplace(Args&&...args)
	{
		reset();
		construct<T>(std::forward<Args>(args)...);
	}

	/*!
	 * Sets variant only when types match, or variant is empty.
	 */
	template<typename T>
	bool try_set(T const& v)
	{
		if (empty()) {
			construct<T>(v);
			return true;
		}
		// TODO: is_assignable
		if (check_type<T>()) {
			assign(v);
			return true;
		}
		return false;
	}

	/*!
	 * Move value v into variant if it holds same type
	 */
	template<typename T>
	auto try_set(T&& v) -> bool_if< !is_reference<T> >
	{
		if (empty()) {
			construct<T>(std::move(v));
			return true;
		}
		if (check_type<T>()) {
			assign(std::move(v));
			return true;
		}
		return false;
	}

	/*!
	 * Extract value from variant.
	 * \return
	 *     true if types match and \a target was modified, false otherwise.
	 */
	template<typename T>
	bool get(T& target) const
	{
		if (check_type<T>()) {
			target = *reinterpret_cast<T const*>(&storage);
			return true;
		}
		return false;
	}

	/*!
	 * Extract value from variant.
	 */
	template<typename T>
	T* get()
	{
		if (check_type<T>())
			return reinterpret_cast<T*>(&storage);
		return nullptr;
	}

	/*!
	 * Extract value from variant.
	 */
	template<typename T>
	T const* get() const
	{
		if (check_type<T>())
			return reinterpret_cast<T const*>(&storage);
		return nullptr;
	}

	/*!
	 * Destroy current value and mark variant as empty.
	 */
	void reset()
	{
		if (empty())
			return;
		destroy();
		index = invalid;
	}

	/*!
	 * This type is used to avoid accidental comparisons of
	 * indices from different variant types.
	 */
	enum class index_t : size_t { };
	//! Invalid index (empty variant)
	static constexpr index_t invalid = index_t(std::numeric_limits<size_t>::max());
	//! Index of particular type
	template<typename T>
	static constexpr index_t index_of = index_t(aw::index_of<T, Ts...>);

	/*!
	 * Check if variant is empty.
	 */
	bool empty() const
	{
		return index == invalid;
	}

	/*!
	 * Check if variant contains type T.
	 */
	template<typename T>
	bool check_type() const
	{
		return !empty() && (index == index_of<T>);
	}

	/*
	 * Get index of currently stored type.
	 */
	index_t type_index() const
	{
		return index;
	}

	/*!
	 * Apply a functor to variant.
	 * Functor must have an * template overloaded operator(),
	 * with template parameter T, * and argument T& or T const&:
	 *
	 * `template<typename T> R operator()(T&, Args...);`
	 *
	 * \arg func
	 *    Instance of a functor.
	 * \return
	 *    Return value of the functor, if present.
	 */
	template<typename Functor>
	auto apply(Functor func) -> typename Functor::return_type
	{
		auto sptr = reinterpret_cast<void*>(&storage);
		return _impl::apply_dispatch(*this, sptr, func);
	}

	template<typename Functor>
	auto apply(Functor func) const -> typename Functor::return_type
	{
		auto sptr = reinterpret_cast<void const*>(&storage);
		return _impl::apply_dispatch(*this, sptr, func);
	}

private:
	/*!
	 * Different instantiations of variant should have access to
	 * eachother's internals, as though they are of same class.
	 */
	template<typename... Os>
	friend class variant;


	// Helpers
	/*
	 * Constructs new object of type T and marks T as current type.
	 */
	template<typename T, typename... Args>
	void construct(Args&&... args)
	{
		static_assert(index_of<T> != invalid, "Invalid type");
		index = index_of<T>;
		new (&storage) T(std::forward<Args>(args)...);
	}

	/*
	 * Calls assignment operator on currently held object.
	 * Doesn't do typechecking, that should be done by public interface.
	 */
	template<typename T>
	void assign(T const& other)
	{
		*reinterpret_cast<T*>(&storage) = other;
	}

	/*
	 * Destroys currently held value by applying Destroy functor.
	 */
	void destroy()
	{
		apply(_impl::variant_destroy_visitor{});
	}

	template<typename Variant>
	void copy_from(Variant&& other)
	{
		using Visitor = _impl::variant_copy_assign_visitor<variant>;
		if (other.empty())
			reset();
		else
			other.apply(Visitor{*this});
	}

	template<typename Variant>
	void move_from(Variant&& other)
	{
		using Visitor = _impl::variant_copy_assign_visitor<variant>;
		if (other.empty()) {
			reset();
		} else {
			other.apply(Visitor{*this});
			other.reset();
		}
	}

	// Copies value held by one variant into another
	struct copy_construct_visitor {
		using return_type = void;

		copy_construct_visitor(variant& self)
			: self(self)
		{}

		template<typename T>
		void operator()(T const& value)
		{
			self.construct<T>(value);
		}

	private:
		variant& self;
	};

	// Moves value held by one variant into another
	struct move_construct_visitor {
		using return_type = void;

		move_construct_visitor(variant& self)
			: self(self)
		{
		}

		template<typename T>
		void operator()(T& value)
		{
			self.construct<T>(std::move(value));
		}

	private:
		variant& self;
	};

private:
	// Storage
	using Storage = typename std::aligned_storage<size, align>::type;

	index_t index = invalid;
	Storage storage;
};

template<typename>
constexpr size_t variant_size = -1;
template<typename...Ts>
constexpr size_t variant_size<variant<Ts...>> = sizeof...(Ts);

template<size_t I, typename Variant>
struct variant_alternative_t;
template<size_t I, typename...Ts>
struct variant_alternative_t<I,variant<Ts...>> {
	using type = at_index<I,Ts...>;
};

//! Convert index to type
template<size_t I, typename Variant>
using variant_alternative = typename variant_alternative_t<I,Variant>::type;
} // namespace aw

#include <aw/types/bits/variant_dispatch.h>
#endif//aw_types_variant_h
