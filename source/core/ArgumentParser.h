/*
 * Copyright (C) 2014-2015  absurdworlds
 * Copyright (C) 2015       Hedede <hededrk@gmail.com>
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_ArgumentParserImpl_
#define _hrengin_ArgumentParserImpl_
#include <deque>

#include <hrengin/core/ArgumentParser.h>

namespace hrengin {
namespace core {

class ArgumentParserImpl : public ArgumentParser {
public:
	ArgumentParserImpl(char** argv);
	virtual ~ArgumentParserImpl()
	{
	}

	virtual i32 getNextArgument (Argument& tok);
private:
	void parse(char** argv);
	void parseToken(char* argv);
	std::string readString(char* argv);

	std::deque<Argument> tokens_;
	bool term_;
};

} //namespace core
} //namespace hrengin
#endif//_hrengin_ArgumentParserImpl_
