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
#include <aw/utility/to_string.h>
#include <aw/io/input_stream.h>
#include <aw/log/log.h>
#include <aw/fileformat/hdf/export.h>
namespace aw {
namespace hdf {
struct token {
	struct position {
		unsigned line = 0;
		unsigned col  = 0;

		friend std::string to_string(position pos)
		{
			using aw::to_string;
			std::string ret;
			ret.append(to_string(pos.line));
			ret.append(1,',');
			ret.append(to_string(pos.col));
			return ret;
		}
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

struct Lexer {
	Lexer(io::input_stream& stream, log* logger = nullptr)
		: stream{stream}, logger{logger}
	{
		getToken();
	}

	~Lexer() = default;

	token getToken();
	token peekToken();

	void message(std::string const& msg, token::position pos)
	{
		report(log::info, msg, pos);
	}
	void warning(std::string const& msg, token::position pos)
	{
		report(log::warning, msg, pos);
	}
	void error(std::string const& msg, token::position pos)
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

	token readToken();

	std::string readString();
	std::string readNumber();
	std::string readName();
	std::string readIllegalToken();

	char get();
	char next();
	char peek();

	template<typename Func>
	char skip(Func condition);

	char fastForward();

private:
	io::input_stream& stream;
	log* logger;

	token tok;
	token::position pos{1, 1};
};
} // namespace io
} // namespace aw
#endif//aw_fileformat_hdf_lexer_h
