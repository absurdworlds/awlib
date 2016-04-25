/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_BufferedStream_
#define _aw_BufferedStream_
#include <aw/io/InputStream.h>

namespace aw {
namespace io {
class ReadFile;

/*!
 * Implements InputStream interface as a file stream.
 * Provies sequential file access,
 */
class AW_IO_EXP InputFileStream : public InputStream {
public:
	InputFileStream(ReadFile& file);
	virtual ~InputFileStream() = default;

	//FileStream() = delete;
	//FileStream(FileStream&) = delete;

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
	virtual size_t position() const;

private:
	ReadFile& source;
	char cur;
	size_t pos;
	size_t size;
};

} //namespace io
} //namespace aw
#endif//_aw_BufferedStream_
