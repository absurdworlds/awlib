/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_stringutils_
#define _hrengin_stringutils_

#include <hrengin/common/compiler_setup.h>

#include <cstring>

#include <string>

#include <hrengin/core/api.h>

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

//! Generic strlen
template<typename char_type>
size_t strlen_g (char_type const* str)
{
	char_type const* s = str;
	while(*s) {
		s++;
	}
	return s - str;
}

//! Get file extension from string
HR_CORE_API std::string getFileExtension(std::string& dest, std::string const& path);

//! This struct is used for more convenient storage of POD character arrays
struct PodString {
	size_t length;
	char* data;
};

inline PodString createPodString(std::string s) 
{
	PodString ps;
	ps.length = s.length();
	ps.data = new char[ps.length+1];
	strcpy((char *)ps.data,s.c_str());
	return ps;
}

inline PodString createPodString(const char* s) 
{
	PodString ps;
	ps.length = strlen(s);
	ps.data = new char[ps.length+1];
	strcpy((char *)ps.data,s);
	return ps;
}

} // namespace hrengin

#endif //_hrengin_stringutils_
