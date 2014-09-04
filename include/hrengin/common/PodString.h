#ifndef _hrengin_PodString_
#define _hrengin_PodString_

#include <string>
#include <cstring>

#include <hrengin/common/types.h>

namespace hrengin {

/*
   This struct is used fro more convenient storage of POD character arrays
 */
struct PodString {
	size_t length;
	u8* data;
};


PodString createPodString(std::string s) 
{
	PodString ps;
	ps.length = s.length();
	ps.data = new u8[ps.length+1];
	strcpy((char *)ps.data,s.c_str());
	return ps;
}
PodString createPodString(const char* s) 
{
	PodString ps;
	ps.length = strlen(s);
	ps.data = new u8[ps.length+1];
	strcpy((char *)ps.data,s);
	return ps;
}

} // namespace hrengin

#endif//_hrengin_PodString_