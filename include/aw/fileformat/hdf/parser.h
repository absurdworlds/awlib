/*
 * Copyright (C) 2014-2015  absurdworlds
 * Copyright (C) 2015       Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_fileformat_hdf_reader_h
#define aw_fileformat_hdf_reader_h
#include <string>

#include <aw/fileformat/hdf/value.h>
#include <aw/fileformat/hdf/shared.h>
#include <aw/fileformat/hdf/lexer.h>

#include <aw/io/input_stream.h>

namespace aw {
namespace hdf {
/*!
 * Object returned by HDF parser
 */
struct Object {
	enum Kind {
		Null = 0,
		Node,
		NodeEnd,
		Value,
	};

	Kind type = Null;
	std::string name;
	struct Value val;
};

/*!
 * HDF 1.3 parser, provides a simple interface for reading
 * aw::hdf files.
 */
struct Parser {
	Parser(io::input_stream& stream, aw::log* logger = nullptr)
		: lex{stream, logger}
	{}

	~Parser() = default;

	//! Read an object
	bool read(Object& obj);

	//! Skip current node
	void skip_node();

protected:
	void processCommand();

	Value read_value();

	template <typename T>
	Value parse_value();
	Value parse_value(token id);
	Value deduce_value(token tok);

	void skip_vector();

	template <typename T>
	std::vector<T> parse_vector(token::position beg);
	Value parse_vector(token id);
	Value deduce_vector(token::position beg);

private:
	Lexer lex;
	size_t depth = 0;
};
} // namespace io
} // namespace aw
#endif//aw_fileformat_hdf_reader_h
