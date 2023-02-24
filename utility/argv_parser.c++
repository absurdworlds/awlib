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

namespace aw::utils {
namespace {
// Used to avoid extra branching
char const dummy = 0;
}

argv_parser::argv_parser(char const* const* argv)
	: argv(argv), arg_group(&dummy)
{
}

static void check_for_equals(argument& arg)
{
	auto pos = arg.name.find('=');
	if (pos == arg.name.npos)
		return;
	arg.value = arg.name.substr(pos+1);
	arg.name  = arg.name.substr(0, pos);
}

argument argv_parser::next_arg(char const* arg)
{
	using namespace std::string_literals;

	if (*arg != '-')
		return argument(arg);

	++arg; // Eat '-'

	argument tok;

	switch (*arg) {
	case 0:
		return argument("-"s);
	case '-':
		++arg;
		tok.long_option = true;
		if (*arg == 0) {
			tok.type = argument::delim;
			tok.name = "--";
		} else {
			tok.type = argument::option;
			tok.name = std::string(arg);
			check_for_equals(tok);
		}
		break;
	default:
		tok.type = argument::option;
		tok.name = *(arg++);
		arg_group = arg;
	}

	return tok;
}

optional<argument> argv_parser::parse_argument()
{
	if (*arg_group != 0) {
		argument tok;
		tok.type = argument::option;
		tok.name = *(arg_group++);
		return tok;
	}

	if (*argv == nullptr)
		return nullopt;

	return next_arg(*argv++);
}

optional<argument> argv_parser::parse_option()
{
	auto arg = parse_argument();
	if (arg && arg->value.empty())
		arg->value = get_param();
	return arg;
}

std::string argv_parser::get_param()
{
	if (*arg_group != 0) {
		std::string tmp(arg_group);
		arg_group = &dummy; // reset 'args'
		return tmp;
	}

	if (*argv == nullptr)
		return "";

	return std::string(*argv++);
}
} //namespace aw::utils
