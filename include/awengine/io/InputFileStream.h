/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_BufferedStream_
#define _awrts_BufferedStream_
#include <awengine/io/InputStream.h>

namespace awrts {
namespace io {
class ReadFile;

//! Class defines an interface for file stream
class AW_IO_EXP InputFileStream : public InputStream {
public:
	InputFileStream(ReadFile& file);
	virtual ~InputFileStream() = default;

	/*!
	 * Look at current character without extracting it
	 */
	virtual bool peek(char& c);

	/*!
	 * Extract current character from stream.
	 */
	virtual bool get(char& c);

	/*!
	 * Skip current character and look at next one, without
	 * extracting it.
	 * Equivalent to
	 * 	get(c) && peek(c);
	 */
	virtual bool next(char& c);
	
	/*!
	 * Get position in stream
	 */
	virtual size_t getPos() const;

private:
	ReadFile& source;
	char cur;
	size_t pos;
	size_t size;
};

} //namespace io
} //namespace awrts
#endif//_awrts_BufferedStream_
