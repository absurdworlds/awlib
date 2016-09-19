/*
 * Copyright (C) 2014-2015  absurdworlds
 * Copyright (C) 2015       Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_hdf_Lexer_impl_
#define _aw_hdf_Lexer_impl_
#include <string>

namespace aw {
namespace hdf {
struct Token {
	enum Kind {
		Invalid,
		Eof,
		Name,
		Number,
		String,
		Equals,
		Colon,
		Comma,
		Bang,
		NodeBegin,
		NodeEnd,
		VecBegin,
		VecEnd,
	};

	Token()
		: type(Kind::Invalid)
	{ }
	
	Token(Kind type)
		: type(type)
	{ }

	Token(Kind type, std::string val)
		: type(type), value(val)
	{ }

	Token(Kind type, std::string val, size_t pos)
		: type(type), value(val), pos(pos)
	{ }

	Kind type;
	std::string value;
	size_t pos;
};

struct Lexer {
	Lexer(io::input_stream& stream)
		: stream(stream)
	{
		getToken();
	}

	virtual ~Lexer() = default;

	Token getToken();
	Token peekToken();

	void error(std::string msg);
private:
	Token readToken();

	std::string readString();
	std::string readNumber();
	std::string readName();
	std::string readIllegalToken();

	void fastForward();
	void skipLine();
	void skipWhitespace();
	void skipInlineWhitespace();
	template<typename Func>
	void skip(Func condition);

	io::input_stream& stream;

	Token tok;
};
} // namespace io
} // namespace aw
#endif//_aw_hdf_Lexer_impl_
