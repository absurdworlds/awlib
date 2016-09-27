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
	Value convertValue(Type type);
	Value convertValue(token tok);
	Value parseVector(Type type);
	Value parseVector();

	template <typename T>
	bool parseVector(T& vec, size_t vecsize);

	void message() {  }

	enum class State {
		Idle = 0,
		Object,
		Node,
		Command,
		Value,
		Data,
		Panic
	};

private:
	Lexer lex;
	State state = State::Idle;
	size_t depth = 0;
};
} // namespace io
} // namespace aw
#endif//aw_fileformat_hdf_reader_h
