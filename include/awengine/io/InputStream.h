/*
 * Copyright (C) 2014-2015  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_CharacterStream_
#define _awrts_CharacterStream_
#include <awengine/common/types.h>

#include <awengine/io/io.h>

namespace awrts {
namespace io {
//! Class defines an interface for input streams
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
	 * Get position in stream
	 */
	virtual size_t getPos() const = 0;
};

} // namespace io
} // namespace awrts
#endif//_awrts_CharacterStream_
