/*
 * Copyright (C) 2016-2023 Hudd <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_types_char_buffer_h
#define aw_types_char_buffer_h
#include <aw/types/string_view.h>
#include <memory_resource>
#include <utility>
namespace aw::script {
/*!
 * An immutable character buffer with optional ownership semantics.
 * In other words, it can act as a move-only std::string or
 * as std::string_view, depending on whether it owns the data.
 *
 * The buffer is move-only (transfers ownership, but keeps view to the data),
 * and the data is immutable once the buffer is constructed.
 *
 * An example use case for this is awscript compiler: you can pass
 * a statically compiled string (in which case the buffer doesn't own
 * the data), or read data from a file (in which case the data is
 * owned by the buffer).
 *
 * Note that it is a very specific use case, so you probably shouldn't
 * be using this class unless you know what you're doing.
 *
 * Also note that it doesn't support custom allocators so far.
 */
class char_buffer {
public:
	enum Copy_data { copy_data };

	/*!
	 * Construct a non-owning char_buffer from a string_view
	 */
	explicit char_buffer(string_view view)
		: view(view.data())
	{
	}

	/*!
	 * Construct an owning char_buffer by copying data from a string_view
	 */
	char_buffer(string_view source, Copy_data /* copy_data */)
		: buffer(allocate(source.size()))
		, length(source.size())
		, view(buffer, length)
	{
		std::copy(source.begin(), source.end(), buffer);
	}

	/*!
	 * Low-level constructor for an owning buffer. Use with care.
	 * \param data Pointer to the data. Must be valid.
	 * \param length Length of the data. Must be equal to the size of allocated data.
	 */
	char_buffer(char* data, size_t length)
		: char_buffer(data, length, length)
	{
	}

	/*!
	 * Low-level constructor for an owning buffer. Use with care.
	 * \param data Pointer to the data. Must be valid.
	 * \param length Length of the data. Must be equal to the size of allocated data.
	 * \param slice Length of iterable data.
	 */
	char_buffer(char* data, size_t length, size_t slice)
		: buffer(data)
		, length(length)
		, view(data, slice)
	{
	}

	/*!
	 * Transfer ownership from another char_buffer.
	 * \param other Buffer to take ownership from. It loses the ownership of the data,
	 *              but retains a view into it. In other words, it can be safely used
	 *              as long as it doesn't outlive the newly created char_buffer.
	 */
	char_buffer(char_buffer&& other) noexcept
		: length(other.length)
		, buffer(std::exchange(other.buffer, nullptr))
		, view(other.view)
	{
	}

	char_buffer& operator=(char_buffer&& other) noexcept
	{
		free();
		buffer = std::exchange(other.buffer, nullptr);
		length = std::exchange(other.length, 0);
		view = other.view;
		return *this;
	}

	~char_buffer()
	{
		free();
	}

	char const* begin() const
	{
		return view.data();
	}

	char const* end() const
	{
		return view.data() + view.size();
	}

	const char* data() const
	{
		return buffer ? buffer : view.data();
	}

	size_t size() const
	{
		return buffer ? length : view.size();
	}

	size_t view_size() const
	{
		return view.size();
	}

	explicit operator std::string_view() const
	{
		return view;
	}

private:
	bool own_buffer() const
	{
		return buffer != nullptr;
	}

	char* allocate(size_t length) const
	{
		return new char[length];
	}

	void free()
	{
		if (!own_buffer())
			return;

		delete[] buffer;
		buffer = nullptr;
		length = 0;
		view = {};
	}

private:
	char* buffer = nullptr;
	size_t length = 0;
	string_view view;
};
} // namespace aw::script
#endif//aw_types_char_buffer_h
