/*
 * Copyright (C) 2014-2015  absurdworlds
 * Copyright (C) 2015       Hedede <hededrk@gmail.com>
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include "ArgumentParser.h"

namespace aw {
namespace core {
ArgumentParser* createArgumentParser(char** argv)
{
	return new impl_::ArgumentParser(argv);
}

namespace impl_ {
ArgumentParser::ArgumentParser(char** argv)
	: term_(false)
{
	parse(argv);
}

i32 ArgumentParser::getNextArgument(Argument& tok)
{
	// bug: because it pops element first, and then returns size,
	// arg parser returned 0, when there was actually an element
	// TODO: ^ I think it should just return opt<Argument>
	// And if needed to check number of arguments left, there should be
	// separate method
	size_t size = tokens_.size();
	if(!tokens_.empty()) {
		tok = tokens_.back();
		tokens_.pop_back();
	}
	return size;
}

void ArgumentParser::parse(char** argv)
{
	while(*argv != 0)
		parseToken(*argv++);
}

void ArgumentParser::parseToken (char* argv)
{
	Argument tok;

	if(term_ || *argv != '-') {
		tok.type = Argument::Operand;
		tok.name = readString(argv);
		tokens_.push_front(tok);
		return;
	}

	++argv;

	if(*argv == 0) {
		tok.type = Argument::Operand;
		tok.name = '-';
	} else if (*argv == '-') {
		++argv;
		if(*argv == 0) {
			tok.type = Argument::Delim;
			tok.name = "--";
			term_ = true;
		} else {
			tok.type = Argument::Option;
			tok.name = readString(argv);
			tok.longOpt = true;
		}
	} else {
		tok.type = Argument::Option;
		tok.name = *(argv++);
		while (*argv != 0) {
			tokens_.push_front(tok);
			tok.name = *(argv++);
		}
	}

	tokens_.push_front(tok);
}

std::string ArgumentParser::readString (char* argv)
{
	return std::string(argv);
}

} //namespace impl_
} //namespace core
} //namespace aw
