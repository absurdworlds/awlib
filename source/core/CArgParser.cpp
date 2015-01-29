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
namespace core {
IArgParser* createArgParser (char** argv)
{
	return new CArgParser(argv);
}

CArgParser::CArgParser(char** argv)
	: term_(false)
{
	parse(argv);
}

i32 CArgParser::getToken (ClineArg& tok)
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
		parseToken(*(argv++));
	}
}

void CArgParser::parseToken (char* argv)
{
	ClineArg tok;

	if(term_ || *argv != '-') {
		tok.type = ClineArg::Operand;
		tok.name = readString(argv);
		tokens_.push_front(tok);
		return;
	}

	++argv;

	tok.type = ClineArg::Option;
	if(*argv == 0) {
		tok.name = '-';
	} else if (*argv == '-') {
		++argv;
		if(*argv == 0) {
			tok.type = ClineArg::Delim;
			tok.name = "--";
			term_ = true;
		} else {
			tok.longOpt = true;
			tok.name = readString(argv);
		}
	} else {
		tok.name = *(argv++);
		do {
			tokens_.push_front(tok);
			tok.name = *(argv++);
		} while (*argv != 0);
	}
	
	tokens_.push_front(tok);
}

std::string CArgParser::readString (char* argv)
{
	return std::string(argv);
}

} //namespace core
} //namespace hrengin
