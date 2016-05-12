/*
 * Copyright (C) 2016  Hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_utility_result_h
#define aw_utility_result_h
#include <cassert>
#include <aw/types/types.h>
#include <aw/utility/storage.h>
namespace aw {
inline namespace utility {

/*
namespace _impl {
template<typename T>
struct error {
	error(T const& value) : value(value) {}
	error(T&& value) : value(std::move(value)) {}
	T value;
};
template<typename T>
struct result {
	result(T const& value) : value(value) {}
	result(T&& value) : value(std::move(value)) {}
	T value;
};
} // namespace _impl*/

struct error_tag {};
struct value_tag {};

/*!
 * Simple helper, which can hold either a value, or an error.
 */
template <typename T, typename E>
struct result {
	using value_type = T;
	using error_type = E;

	/*!
	 * Construct result from copy of \a value.
	 *
	 * \note
	 * Pass `value_tag{}` as argument to disambiguate
	 * between error type and value type (if both
	 * can be constructed from same value).
	 */
	result(T const& value, value_tag = value_tag{})
		: is_error(false)
	{
		construct_value(value);
	}

	/*!
	 * Construct error.
	 */
	result(E const& error, error_tag = error_tag{})
		: is_error(true)
	{
		construct_error(error);
	}

	/*!
	 * Move-construct result from \a value.
	 */
	result(T&& value, value_tag = value_tag{})
		: is_error(false)
	{
		construct_value(std::move(value));
	}

	/*!
	 * Move-construct error.
	 */
	result(E&& error, error_tag = error_tag{})
		: is_error(true)
	{
		construct_error(std::move(error));
	}

	template<typename...Args>
	result(value_tag, Args&&... args)
		: is_error(false)
	{
		construct_value(std::forward<Args>(args)...);
	}

	template<typename...Args>
	result(error_tag, Args&&... args)
		: is_error(true)
	{
		construct_error(std::forward<Args>(args)...);
	}

	template<typename OtherT, typename OtherE>
	result(result<OtherT,OtherE> const& other)
		: is_error(other.is_error)
	{
		if (!is_error)
			construct_value(other.value());
		else
			construct_error(other.error());
	}


	template<typename OtherT, typename OtherE>
	result(result<OtherT,OtherE>&& other)
		: is_error(other.is_error)
	{
		if (!is_error)
			construct_value(std::move(other.value()));
		else
			construct_error(std::move(other.error()));
	}

	~result()
	{
		destroy();
	}

	bool has_error() const
	{
		return is_error;
	}

	/*!
	 * Check if result holds a value.
	 * \return
	 *    `true` if result holds a value,
	 *    `false` if result holds an error.
	 */
	explicit operator bool() const
	{
		return !is_error;
	}

	/*!
	 * Get value from result.
	 *
	 * Behaviour is undefined if result holds an error.
	 */
	T& value() &
	{
		return *get_value();
	}
	T const& value() const&
	{
		return *get_value();
	}
	T&& value() &&
	{
		return std::move(*get_value());
	}
	T const&& value() const&&
	{
		return std::move(*get_value());
	}

	/*!
	 * Get error from result.
	 *
	 * Behaviour is undefined if result holds a value.
	 */
	E& error() &
	{
		return *get_error();
	}
	E const& error() const&
	{
		return *get_error();
	}
	E&& error() &&
	{
		return std::move(*get_error());
	}
	E const&& error() const&&
	{
		return std::move(*get_error());
	}

private:
	void destroy()
	{
		if (!is_error)
			storage_.template destroy<value_type>();
		else
			storage_.template destroy<error_type>();
	}

	template <typename... Args>
	void construct_value(Args&&...args)
	{
		storage_.template construct<T>(std::forward<Args>(args)...);
	}

	template <typename... Args>
	void construct_error(Args&&...args)
	{
		storage_.template construct<E>(std::forward<Args>(args)...);
	}

	T* get_value()
	{
		assert(!is_error);
		return storage_.template get<T>();
	}

	T const* get_value() const
	{
		assert(!is_error);
		return storage_.template get<T>();
	}

	E* get_error()
	{
		assert(is_error);
		return storage_.template get<E>();
	}

	E const* get_error() const
	{
		assert(is_error);
		return storage_.template get<E>();
	}

	storage<T, E> storage_;
	bool is_error;
};

template<class T, class E, typename... Args>
result<T,E> make_result(Args&&... args)
{
	return {value_tag{}, std::forward<Args>(args)...};
}

template<class T, class E, typename... Args>
result<T,E> make_error(Args&&... args)
{
	return {error_tag{}, std::forward<Args>(args)...};
}
} // namespace utility
} // namespace aw
#endif//aw_utility_result_h
