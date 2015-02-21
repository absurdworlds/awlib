/*
 * Copyright (C) 2014-2015  absurdworlds
 * Copyright (C) 2015       Hedede <hededrk@gmail.com>
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_CArgParser_
#define _hrengin_CArgParser_
#include <deque>

#include <hrengin/core/IArgParser.h>

namespace hrengin {
namespace core {

class CArgParser : public IArgParser {
public:
	CArgParser (char** argv);
	virtual ~CArgParser ()
	{
	}

	virtual i32 getNextArgument (ClineArg& tok);
private:
	void parse (char** argv);
	void parseToken (char* argv);
	std::string readString (char* argv);

	std::deque<ClineArg> tokens_;
	bool term_;
};

} //namespace core
} //namespace hrengin
#endif//_hrengin_IArgParser_
