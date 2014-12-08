/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <cstdio>

#include <hrengin/core/IArgParser.h>

int main (int, char** v)
{
	using namespace hrengin;
	core::IArgParser* a = core::createArgParser(v);
	core::ClineArg tok;

	while(a->getToken(tok)) {
		char c;
		switch(tok.type) {
		case core::ClineArg::Option:
			c = tok.longOpt ? 'l' : 'o';
			break;
		case core::ClineArg::Delim:
			c = 'd';
			break;
		case core::ClineArg::Argument:
			c = 'a';
			break;
		}	
		printf("%c %s\n", c, tok.name.c_str());
	}

	return 0;
}
