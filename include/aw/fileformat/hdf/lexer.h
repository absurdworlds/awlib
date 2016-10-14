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
#include <aw/io/input_stream.h>
#include <aw/log/log.h>
#include <aw/fileformat/hdf/export.h>
namespace aw {
namespace hdf {
struct token {
	struct position {
		unsigned line = 0;
		unsigned col  = 0;

		friend std::string aw::hdf::to_string(position pos);
	};

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
	position pos;
};

AW_HDF_EXP std::string to_string(token::position pos);

struct Lexer {
	Lexer(io::input_stream& stream, log* logger = nullptr)
		: stream{stream}, logger{logger}
	{
		tok = readToken();
	}

	~Lexer() = default;

	token getToken();
	token peekToken();
	token nextToken()
	{
		return tok = readToken();
	}

	void message(string_view msg, token::position pos)
	{
		report(log::info, msg, pos);
	}
	void warning(string_view msg, token::position pos)
	{
		report(log::warning, msg, pos);
	}
	void error(string_view msg, token::position pos)
	{
		report(log::error, msg, pos);
	}

private:
	void report(log::level lvl, std::string msg, token::position pos)
	{
		if (logger) {
			msg = to_string(pos) + ':' + msg;
			logger->message(lvl, "HDF", msg);
		}
	}

	void count_line(char c)
	{
		if (c == '\n') {
			++pos.line;
			pos.col = 1;
		} else if (c != 0) {
			++pos.col;
		}
	}

	char get()
	{
		char c;
		stream.get(c);
		count_line(c);
		return c;
	}
	char peek()
	{
		char c;
		stream.peek(c);
		return c;
	}
	char next()
	{
		return get(), peek();
	}

	template<typename Func>
	char skip(Func condition);
	char skip_comment();

	template<typename Func>
	std::string read(Func condition);
	std::string read_string();

	token readToken();

private:
	io::input_stream& stream;
	log* logger;

	token tok;
	token::position pos{1, 1};
};
} // namespace io
} // namespace aw
#endif//aw_fileformat_hdf_lexer_h
