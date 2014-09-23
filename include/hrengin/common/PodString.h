/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_PodString_
#define _hrengin_PodString_

#include <string>
#include <cstring>

namespace hrengin {

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

#endif//_hrengin_PodString_
