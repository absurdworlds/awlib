/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include "CArgParser.h"

namespace hrengin {
namespace io {
IArgParser* createArgParser (char** argv)
{
	return new CArgParser(argv);
}

CArgParser::CArgParser(char** argv)
	: term_(false)
{
	parse(argv);
}

i32 CArgParser::getToken (IArgParser::Token& tok)
{
	if(tokens_.empty()) {
		return 0;
	}

	tok = tokens_.back();
	tokens_.pop_back();

	return 1;
}

void CArgParser::parse (char** argv)
{
	while(*argv != 0) {
		parseToken(*argv);
		++argv;
	}
}

void CArgParser::parseToken (char* argv)
{
	IArgParser::Token tok;

	if(term_ || *argv != '-') {
		tok.type = IArgParser::Argument;
		tok.name = readString(argv);
		tokens_.push_front(tok);
		return;
	}

	++argv;

	tok.type = IArgParser::Option;
	if(*argv == 0) {
		tok.name = '-';
	} else if (*argv == '-') {
		++argv;
		if(*argv == 0) {
			tok.name = "--";
			term_ = true;
		} else {
			tok.type = IArgParser::LongOpt;
			tok.name = readString(argv);
		}
	} else {
		tok.name = *argv;
		argv++;
		do {
			tokens_.push_front(tok);
			tok.name = *argv;

			argv++;
		} while (*argv != 0);
	}
	
	tokens_.push_front(tok);
}

std::string CArgParser::readString (char* argv)
{
	std::string s;
	while (*argv != 0) {
		s += *argv;
		argv++;
	}
	return s;
}

} //namespace io
} //namespace hrengin
