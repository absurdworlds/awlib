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
#include <aw/types/traits/basic_traits.h>
#include <aw/meta/conditional.h>
#include <aw/meta/list_ops.h>
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
	template<typename T, typename = enable_if<is_in_pack<T,Ts...>>>
	variant(T const& value)
	{
		construct<T>(value);
	}

	template<typename T, typename = enable_if<is_in_pack<T,Ts...>>>
	variant(T&& value)
	{
		construct<T>(std::move(value));
	}

	/*!
	 * Copy variant from another
	 */
	variant(variant const& other)
	{
		if (other.empty()) {
			reset();
			return;
		}

		other.apply(Copy{*this});
	}

	/*!
	 * Move variant from another
	 */
	variant(variant&& other)
	{
		if (other.empty()) {
			reset();
			return;
		}

		other.apply(Move{*this});
		other.reset();
	}

	/*!
	 * Move variant from a subset variant type
	 */
	template<typename... Os>
	variant(variant<Os...> const& other)
	{
		static_assert(!is_same<variant<Os...>, variant<Ts...>>,
		              "Non-template constructor should be used for variant of same type.");
		static_assert(is_subset<meta::list<Os...>, meta::list<Ts...>>,
		              "Other variant type must be a subset.");

		if (other.empty()) {
			reset();
			return;
		}

		other.apply(Copy{*this});
	}

	/*!
	 * Move variant from a subset variant type
	 */
	template<typename... Os>
	variant(variant<Os...>&& other)
	{
		static_assert(!is_same<variant<Os...>, variant<Ts...>>,
		              "Non-template constructor should be used for variant of same type.");
		static_assert(is_subset<meta::list<Os...>, meta::list<Ts...>>,
		              "Other variant type must be a subset.");

		if (other.empty()) {
			reset();
			return;
		}

		other.apply(Move{*this});
		other.reset();
	}

	variant& operator=(variant const& other)
	{
		if (other.empty()) {
			reset();
			return *this;
		}

		other.apply(Copy{*this});
		return *this;
	}

	variant& operator=(variant&& other)
	{
		assert(&other != this);

		if (other.empty()) {
			reset();
			return *this;
		}

		other.apply(Move{*this});
		other.reset();
		return *this;
	}

	template<typename... Os>
	variant& operator=(variant<Os...> const& other)
	{
		static_assert(!is_same<variant<Os...>, variant<Ts...>>,
		              "Non-template operator should be used for variant of same type.");
		static_assert(is_subset<meta::list<Os...>, meta::list<Ts...>>,
		              "Other variant type must be a subset.");

		if (other.empty()) {
			reset();
			return *this;
		}

		other.apply(Copy{*this});
		return *this;
	}

	template<typename... Os>
	variant& operator=(variant<Os...>&& other)
	{
		static_assert(!is_same<variant<Os...>, variant<Ts...>>,
		              "Non-template operator should be used for variant of same type.");
		static_assert(is_subset<meta::list<Os...>, meta::list<Ts...>>,
		              "Other variant type must be a subset.");

		if (other.empty()) {
			reset();
			return *this;
		}

		other.apply(Move{*this});
		other.reset();
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
	 * Sets variant only when types match, or variant is empty.
	 */
	template<typename T>
	bool try_set(T const& v)
	{
		if (empty()) {
			construct<T>(v);
			return true;
		}
		if (check_type<T>()) {
			assign(v);
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
	//! Convert index to type
	template<size_t I>
	using type_at = aw::at_index<I, Ts...>;

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

	struct Copy {
		using return_type = void;

		Copy(variant& self)
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

	struct Move {
		using return_type = void;

		Move(variant& self)
			: self(self)
		{}

		template<typename T>
		void operator()(T& value)
		{
			self.construct<T>(std::move(value));
		}

	private:
		variant& self;
	};

	// Storage
	using Storage = typename std::aligned_storage<size, align>::type;

	index_t index = invalid;
	Storage storage;
};
} // namespace aw
#endif//aw_types_variant_h
