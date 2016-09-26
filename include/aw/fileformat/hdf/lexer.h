/*
 * Copyright (C) 2014-2015  absurdworlds
 * Copyright (C) 2015       Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_fileformat_hdf_lexer_h
#define aw_fileformat_hdf_lexer_h
#include <string>

namespace aw {
namespace hdf {
struct token {


	enum {
		invalid,
		eof,
		name,
		number,
		string,
		equals,
		colon,
		comma,
		bang,
		node_begin,
		node_end,
		vec_begin,
		vec_end,
	} kind = invalid;

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

	token getToken();
	token peekToken();

	void error(std::string msg);
private:
	token readToken();

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

	token tok;
};
} // namespace io
} // namespace aw
#endif//aw_fileformat_hdf_lexer_h
