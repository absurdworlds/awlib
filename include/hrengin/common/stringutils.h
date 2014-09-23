/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_stringutils_
#define _hrengin_stringutils_

#include <string>
#include <hrengin/common/api.h>

namespace hrengin {

//! Functor for finding a string key in a map
template <class Value>
class findKey {
public:
	typedef std::string Key;
	findKey (std::string const& str) : key_(str) { }

	bool operator () (std::pair<Key, Value> const& pair)
	{
		return (pair.first == key_);
	}

	std::string key_;
};

//! Get file extension from string
HR_CORE_API std::string getFileExtension(std::string& dest, const std::string& path);

} // namespace hrengin

#endif //_hrengin_stringutils_
