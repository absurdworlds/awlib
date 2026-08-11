/*
 * Copyright (C) 2014-2015  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <cstdio>

#include <aw/utility/argv_parser.h>

int main(int, char** v)
{
	using namespace aw::utils;

	argv_parser parser(v + 1);

	while (auto r = parser.parse_argument()) {
		argument& arg = *r;

		char c = '?';
		char const* text = arg.name.c_str();
		switch (arg.type) {
		case argument::option:
			c = arg.long_option ? 'l' : 'o';
			break;
		case argument::delim:
			c = 'd';
			break;
		case argument::argument:
			c    = 'a';
			text = arg.value.c_str();
			break;
		case argument::invalid:
			break;
		}

		printf("%c %s\n", c, text);
	}

	return 0;
}
