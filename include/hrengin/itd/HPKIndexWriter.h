/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 2.1 <http://gnu.org/licenses/lgpl-2.1.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_HPKIndexWriter_
#define _hrengin_HPKIndexWriter_
#include <ostream>
#include <string>

#include <hrengin/common/types.h>
#include <hrengin/itd/itd.h>

namespace hrengin {
namespace itd {
/*!
 * Interface for building HPKA index
 */
class HPKIndexWriter {
public:
	virtual ~HPKIndexWriter ()
	{
	}

	/*!
	 * Add file to index
	 */
	virtual void addFile (std::string const& path, u64 id) = 0;
	/*!
	 * Write index to a stream
	 */
	virtual void write (std::ostream& target) = 0;
};

} //namespace itd
} //namespace hrengin
#endif//_hrengin_HPKIndexWriter_
