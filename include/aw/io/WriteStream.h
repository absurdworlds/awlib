/*
 * Copyright (C) 2015  absurdworlds
 * Copyright (C) 2015  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_OStream_
#define _aw_OStream_
#include <string>

#include <aw/types/types.h>
#include <aw/types/string_view.h>

namespace aw {
namespace io {
/*!
 * This class provides unified interface for sequential data writing.
 */
class WriteStream {
public:
	/*! Write a character into the output stream. */
	virtual i32 put(char c) = 0;

	/*! Write a string into the output stream */
	virtual i32 put(string_view str) = 0;

	virtual i32 write(const char* data, size_t size) = 0;

	/*!
	 * Get current position in the stream.
	 */
	virtual size_t position() const = 0;
};

} // namespace io
} // namespace aw
#endif//_aw_OStream_
