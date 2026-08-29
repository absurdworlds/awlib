/*
 * Copyright (C) 2016  Hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_utility_storage_h
#define aw_utility_storage_h
#include <algorithm>
#include <cstddef>
#include <type_traits>
#include <utility>
#include <aw/meta/list_ops.h>
namespace aw {
inline namespace utility {
template <typename...Types>
class storage {
	static constexpr size_t size_value = std::max({ size_t(1), sizeof(Types)... });

public:
	static constexpr size_t alignment_value = std::max({ size_t(1), alignof(Types)... });

	void* get_storage()
	{
		return &storage_;
	}

	void const* get_storage() const
	{
		return &storage_;
	}

	template<typename T>
	T* get()
	{
		static_assert(is_in_pack<T,Types...>);
		return reinterpret_cast<T*>(get_storage());
	}

	template<typename T>
	T const* get() const
	{
		static_assert(is_in_pack<T,Types...>);
		return reinterpret_cast<T const*>(get_storage());
	}

	template<typename T>
	void destroy()
	{
		static_assert(is_in_pack<T,Types...>);
		reinterpret_cast<T*>(get_storage())->~T();
	}

	template <typename T, typename... Args>
	void construct(Args&&...args)
	{
		static_assert(is_in_pack<T,Types...>);
		new (get_storage()) T(std::forward<Args>(args)...);
	}

private:
	alignas(alignment_value) std::byte storage_[size_value];
};
} // namespace utility
} // namespace aw
#endif//aw_utility_storage_h
