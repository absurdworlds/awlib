/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 2.1 <http://gnu.org/licenses/lgpl-2.1.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_internal_HPKIndexReader_h
#define aw_internal_HPKIndexReader_h
#include <aw/itd/itd.h>

namespace aw {
namespace itd {
/*!
 * Interface for reading HPKA index
 */
struct HPKIndexReader {
	virtual ~HPKIndexReader() = default;

	/*!
	 * Find a file
	 * \param path Full path to file
	 * \return D of the file or -1
	 */	 
	virtual u64 findFile(std::string const& path) = 0;

	/*!
	 * List all files with paths starting with \a prefix
	 * \param prefix Diectory to list
	 * \return List of files in directory \prefix
	 */
	virtual std::vector<std::string> list(std::string const& prefix) = 0;

	virtual void read() = 0;
};

} //namespace itd
} //namespace aw
#endif//aw_internal_HPKIndexReader_h
