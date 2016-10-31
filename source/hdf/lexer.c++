/*
 * Copyright (C) 2014-2015  absurdworlds
 * Copyright (C) 2015       Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <cassert>
#include <cstdio>

#include <aw/fileformat/hdf/lexer.h>

#include <aw/utility/to_string.h>
#include <aw/utility/string/compose.h>

namespace aw {
namespace hdf {
inline namespace v1 {
std::string to_string(token::position pos)
{
	using aw::to_string;
	std::string ret;
	ret.append(to_string(pos.line));
	ret.append(1,',');
	ret.append(to_string(pos.col));
	return ret;
}

namespace {
bool is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

bool is_num_char(char c)
{
	return is_digit(c) || in(c, '.', 'e', 'E', '+', '-');
}

bool is_name_begin_char(char c)
{
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool is_name_char(char c)
{
	return is_name_begin_char(c) || is_digit(c) || in(c, '-', '_');
}

bool is_whitespace(char c)
{
	return in(c, ' ', '\v', '\t', '\r', '\n');
}

bool is_not_punct(char c)
{
	return !is_whitespace(c) && !in(c, '[', ']', '=', ':', ',');
}
} // namespace


template<typename Func>
char lexer::skip(Func condition)
{
	char c = peek();
	while(condition(c) && c != 0)
		c = next();
	return c;
}

char lexer::skip_comment()
{
	using namespace std::string_literals;
	auto line = [] (char c) { return c != '\n'; };

	char c = peek();
	while (c == '/') {
		if (next() == '/') {
			c = skip( line );
			c = get(); // consume '\n'
		} else {
			error("unexpected token: "s + c, pos);
			c = next(); // skip '/'
		}
	}
	return c;
}

template<typename Func>
std::string lexer::read(Func condition)
{
	std::string val;


	char c = peek();
	while (condition(c)) {
		val += c;
		c = next();
	}

	return val;
}

std::string lexer::read_string() {
	std::string val;

	char c = peek();
	while (c != '"') {
		// When '\' is encountered in a string, skip the '\' and read
		// next character as it is.
		if (c == '\\')
			c = next();
		val += c;
		c = next();
	}

	// consume "
	get();
	return val;
}


token lexer::read_token()
{
	char c = peek();

	while (c == '/' || is_whitespace(c)) {
		if (is_whitespace(c)) c = skip( is_whitespace );
		if (c == '/')         c = skip_comment();
	}

	auto pos = this->pos;

	switch (c) {
	case 0:
		return token{token::eof};
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
		return token{token::number, read(is_num_char), pos};
	case '"':
		c = next(); // consume '"'
		return token{token::string, read_string(), pos};
	case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G':
	case 'H': case 'I': case 'J': case 'K': case 'L': case 'M': case 'N':
	case 'O': case 'P': case 'Q': case 'R': case 'S': case 'T': case 'U':
	case 'V': case 'W': case 'X': case 'Y': case 'Z':
	case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g':
	case 'h': case 'i': case 'j': case 'k': case 'l': case 'm': case 'n':
	case 'o': case 'p': case 'q': case 'r': case 's': case 't': case 'u':
	case 'v': case 'w': case 'x': case 'y': case 'z':
		return token{token::name, read(is_name_char), pos};
	case '=':
		return token{token::equals, {get()}, pos};
	case ':':
		return token{token::colon, {get()}, pos};
	case ',':
		return token{token::comma, {get()}, pos};
	case '!':
		return token{token::bang, {get()}, pos};
	case '[':
		c = next(); // consume '['
		return token{token::node_begin, read(is_name_char), pos};
	case ']':
		return token{token::node_end, {get()}, pos};
	case '{':
		return token{token::vec_begin, {get()}, pos};
	case '}':
		return token{token::vec_end, {get()}, pos};
	default:
		return token{token::invalid, read(is_not_punct), pos};
	}
}

token lexer::peek_token()
{
	return tok;
}

token lexer::get_token()
{
	token tmp = tok;
	tok = read_token();
	return tmp;
}
} // inline namespace v1
} // namespace hdf
} // namespace aw
