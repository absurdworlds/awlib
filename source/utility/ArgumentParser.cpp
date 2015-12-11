/*
 * Copyright (C) 2014-2015  absurdworlds
 * Copyright (C) 2015       Hedede <hededrk@gmail.com>
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <aw/utility/ArgumentParser.h>

namespace aw {
namespace core {
ArgumentParser::ArgumentParser(char const* const* argv)
	: argv(argv), args(0)
{
}

Argument ArgumentParser::nextArg(char const* arg)
{
	if(*arg != '-')
		return std::string(arg);

	++arg; // Eat '-'

	Argument tok;

	switch (*arg) {
	case 0:
		return std::string("-");
	case '-':
		++arg;
		if(*arg == 0) {
			tok.type = Argument::Delim;
			tok.name = "--";
		} else {
			tok.type = Argument::Option;
			tok.name = std::string(arg);
			tok.longOpt = true;
		}
		break;
	default:
		tok.type = Argument::Option;
		tok.name = *(arg++);
		args = arg;
	}

	return tok;
}

opt<Argument> ArgumentParser::parseArgument()
{
	if (args != 0 && *args != 0) {
		Argument tok;
		tok.type = Argument::Option;
		tok.name = *(args++);
		return tok;
	}

	if (*argv == 0)
		return nullopt;

	return nextArg(*argv++);
}
} //namespace core
} //namespace aw
