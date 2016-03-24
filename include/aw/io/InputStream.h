/*
 * Copyright (C) 2014-2015  absurdworlds
 * Copyright (C) 2015  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_IStream_
#define _aw_IStream_
#include <aw/types/types.h>

#include <aw/io/io.h>

namespace aw {
namespace io {
/*!
 * Class provides interface for sequential data access.
 */
// template<typename T>
// TODO: Better name? StreamIn? InStream? IStream?
class InputStream {
public:
	virtual ~InputStream() = default;

	/*!
	 * Look at current character
	 */
	virtual bool peek(char& c) = 0;

	/*!
	 * Extract current character from stream
	 */
	virtual bool get(char& c) = 0;

	/*!
	 * Skip current character and look at next one, without
	 * extracting it.
	 * Equivalent to
	 * 	get(c) && peek(c);
	 */
	virtual bool next(char& c) = 0;
	
	/*!
	 * Get position in stream
	 */
	virtual size_t position() const = 0;
};
} // namespace io
} // namespace aw
#endif//_aw_IStream_
