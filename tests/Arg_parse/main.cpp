/*
 * Copyright (C) 2014-2015  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <cstdio>

#include <aw/utility/ArgumentParser.h>

int main (int, char** v)
{
	using namespace aw;
	core::ArgumentParser parser(v + 1);
	opt<core::Argument> r;

	while(r = parser.parseArgument()) {
		core::Argument& arg = r.value();
		char c;
		switch(arg.type) {
		case core::Argument::Option:
			c = arg.longOpt ? 'l' : 'o';
			break;
		case core::Argument::Delim:
			c = 'd';
			break;
		case core::Argument::Operand:
			c = 'a';
			break;
		}	
		printf("%c %s\n", c, arg.name.c_str());
	}

	return 0;
}
