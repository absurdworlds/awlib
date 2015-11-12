/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 2.1 <http://gnu.org/licenses/lgpl-2.1.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_HPKTreeReader_
#define _aw_HPKTreeReader_
#include <vector>
#include <map>
#include <fstream>

#include <aw/itd/HPKIndexReader.h>

#include "StringBank.h"

namespace aw {
namespace itd {

struct ListEntry {
	ListEntry (u64 name, u64 id)
		: nameOffset(name), id(id)
	{
	}
	u64 nameOffset;
	u64 id;
};

/*!
 * Interface for building HPKA tree index
 */
class HPKTreeReader : public HPKIndexReader {
public:
	HPKTreeReader(std::istream& source);
	virtual ~HPKTreeReader();
	/*!
	 * Find a file
	 * \param path Full path to file
	 * \return D of the file or -1
	 */	 
	virtual u64 findFile(std::string const& path);

	/*!
	 * List all files with paths starting with \a prefix
	 * \param prefix Diectory to list
	 * \return List of files in directory \prefix
	 */
	virtual std::vector<std::string> list(std::string const& prefix);

	void read();
private:
	std::string loadString(u64 ptr);
	void readFiles(std::string dir, u64 ptr, u64 num);
	void readDirs(std::string dir, u64 ptr, u64 num);
	
	std::map<std::string, u64> files;
	std::istream& source;

	size_t base;
};

} //namespace itd
} //namespace aw
#endif//_aw_HPKTreeReader_
