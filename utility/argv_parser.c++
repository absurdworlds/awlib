/*
 * Copyright (C) 2014-2016  absurdworlds
 * Copyright (C) 2016       Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <aw/utility/argv_parser.h>

namespace aw {
namespace utils {
namespace {
// Used to avoid extra branching
char const dummy = 0;
}

argv_parser::argv_parser(char const* const* argv)
	: argv(argv), args(&dummy)
{
}

argument argv_parser::next_arg(char const* arg)
{
	using namespace std::string_literals;

	if (*arg != '-')
		return std::string(arg);

	++arg; // Eat '-'

	argument tok;

	switch (*arg) {
	case 0:
		return "-"s;
	case '-':
		++arg;
		if (*arg == 0) {
			tok.type = argument::delim;
			tok.name = "--";
			tok.long_option = true;
		} else {
			tok.type = argument::option;
			tok.name = std::string(arg);
		}
		break;
	default:
		tok.type = argument::option;
		tok.name = *(arg++);
		args = arg;
	}

	return tok;
}

optional<argument> argv_parser::parse_argument()
{
	if (*args != 0) {
		argument tok;
		tok.type = argument::option;
		tok.name = *(args++);
		return tok;
	}

	if (*argv == 0)
		return nullopt;

	return next_arg(*argv++);
}

std::string argv_parser::get_param()
{
	if (*args != 0) {
		std::string tmp(args);
		args = &dummy; // reset 'args'
		return tmp;
	}

	if (*argv == 0)
		return "";

	return std::string(*argv++);
}
} //namespace utils
} //namespace aw
