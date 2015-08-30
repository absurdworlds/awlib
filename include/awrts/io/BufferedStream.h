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
#include <awrts/io/CharacterStream.h>

namespace awrts {
namespace io {
class ReadFile;

//! Class defines an interface for buffered file stream
class BufferedStream : public CharacterStream {
public:
	virtual ~BufferedStream ()
	{
	}
};

//! Create a buffered file stream
HR_SYS_EXP BufferedStream* createBufferedStream(ReadFile& source);

} //namespace io
} //namespace awrts
#endif//_awrts_BufferedStream_
