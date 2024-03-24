/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 2.1 <http://gnu.org/licenses/lgpl-2.1.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_internal_HPKIndexWriter_h
#define aw_internal_HPKIndexWriter_h
#include <ostream>
#include <string>

#include <aw/itd/itd.h>

namespace aw {
namespace itd {
/*!
 * Interface for building HPKA index
 */
class HPKIndexWriter {
public:
	virtual ~HPKIndexWriter() = default;

	/*!
	 * Add file to index
	 */
	virtual void addFile(std::string const& path, u64 id) = 0;

	/*!
	 * Write index to a stream
	 */
	virtual void write(std::ostream& target) = 0;
};

} //namespace itd
} //namespace aw
#endif//aw_internal_HPKIndexWriter_h
