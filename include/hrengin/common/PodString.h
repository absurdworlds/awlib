#ifndef _hrengin_PodString_
#define _hrengin_PodString_

#include <string>
#include <cstring>

#include <hrengin/common/types.h>

namespace hrengin {

struct PodString {
	PodString(std::string s) 
	{
		length = s.length();
		data = new u8[length+1];
		strcpy((char *)data,s.c_str());
	}
	PodString(const char* s) 
	{
		length = strlen(s);
		data = new u8[length+1];
		strcpy((char *)data,s);
	}
	PodString(PodString& s) = default;

	size_t length;
	u8* data;
};

}

#endif//_hrengin_PodString_