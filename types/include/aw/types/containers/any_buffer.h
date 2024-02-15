#ifndef aw_containers_any_buffer_h
#define aw_containers_any_buffer_h

#include <cstddef>
#include <aw/types/traits/basic_traits.h>

namespace aw {
/**
 * Helper class for storing any type of specified size
 * and alignment. Does not keep track of the stored type,
 * it is up to the user to do so.
 */
template<size_t Size, size_t Align = alignof(void*)>
struct any_buffer {
	static constexpr size_t max_align = Align;
	static constexpr size_t max_size  = Size;

	template<typename T, typename... Args>
	void emplace(Args&&... args)
	{
		using type = std::remove_cvref_t<T>;
		static_assert( alignof(type) <= max_align );
		static_assert( sizeof(type)  <= max_size );

		new (&buffer) type(std::forward<Args>(args)...);
	}

	template<typename T>
	void destroy()
	{
		static_cast<T*>(buffer)->~T();
	}

	template<typename T>
	auto get() -> T&
	{
		using type = std::remove_cvref_t<T>;
		return *ptr<type>();
	}

	template<typename T>
	auto get() const -> const T&
	{
		using type = std::remove_cvref_t<T>;
		return *ptr<type>();
	}

	template<typename T>
	auto ptr() -> T*
	{
		return static_cast<T*>(data());
	}

	template<typename T>
	auto ptr() const -> const T*
	{
		return static_cast<const T*>(data());
	}

protected:
	auto data() -> void*
	{
		return buffer;
	}

	auto data() const -> const void*
	{
		return buffer;
	}

private:
	alignas(max_align) std::byte buffer[max_size];
};

} // namespace aw

#endif // aw_containers_any_buffer_h
