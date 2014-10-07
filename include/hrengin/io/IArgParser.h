/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_IArgParser_
#define _hrengin_IArgParser_

#include <string>

#include <hrengin/core/api.h>

namespace hrengin {
namespace io {

//! Used to parse command line arguments passed to the program
class IArgParser {
public:
	virtual ~IArgParser() 
	{
	}
	virtual void registerOption(char const shortKey, std::string fullKey,
		std::string description) = 0;
	
	virtual void process(std::string args) = 0;
	
};

//! Create an argument parser
HR_CORE_API IArgParser* createArgParser();

} //namespace io
} //namespace hrengin

#endif//_hrengin_IArgParser_
